#include "LegPhysics.h"
#include <iostream>
#include "math.h"
using namespace std; 
#define TODEGREE(R) ((R)/M_PI*180.0)
#define TORADIAN(R) ((R)/180.0*M_PI)
LegPhysics::LegPhysics(int x, int y, int z, float r, float L, char* label) :Component(LEGP) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->radius = r;
	this->length = L;
	
	parent = nullptr;
	nextleg = nullptr;
	xoffset = 0;//for debug mainly
	yoffset = 0;
	zoffset = 0;
	thetax = 0;//make sure 0<=thetax<=180
	thetay =0;
	thetaz = 0;
	thetaxOff = 0;
	thetayOff = 0;
	thetazOff = 0;
	torque = 0;
	omegaX = 0;
	targetuplift = 0;
}
void LegPhysics::gravity(double dt) {
//	c//out << "ypos" << y << "<" << dt << "<" << gF << "<" << motion[1] << endl;
	motion[1] -= dt / 1000.0 * gF*1.3;
	if ((startpoint[1] <= floory )&&motion[1]<0) {
		if (parent == nullptr )
			motion[1] = 0.0001;
		return;
	}
	if ((endpoint[1] <= floory) && motion[1]<0) {
		if (parent == nullptr)
			motion[1] = 0.01;
		return;
	}

}
void LegPhysics::standUpWhenFall() {
	//if (parent==nullptr&& (startpoint[1] <= floory || endpoint[1] <= floory)) {
		if (startpoint[1] > endpoint[1]&& endpoint[2]<startpoint[2]) {
			torque += 4;
		}
		if (startpoint[1] > endpoint[1] && endpoint[2]>startpoint[2]) {
			torque -= 4;
		}
	//}
	
}
void LegPhysics::pointsToPlot(Vec3f start, Vec3f end) {
	x = start[0];
	y = start[1];
	z = start[2];
	double diffx = -end[0]+start[0];
	double diffy = -end[1] +start[1];
	double diffz = -end[2] + start[2];

	if (diffz >= 0 && diffy < 0) {
		thetax = -(180-atanf(diffy / (-(diffz))) / M_PI * 180);
	}
	else if (diffz >= 0 && diffy > 0) {
		thetax = (180 - abs(atanf(diffy / (-(diffz))) / M_PI * 180));
	}
	else{
	thetax = atanf( diffy / (-(diffz)))/M_PI*180;
	}
//	cout <<"thetaxc"<< thetaxc<<","<<thetax << endl;

}
Vec3f LegPhysics::collisionStartWithFloor(Vec3f netforce) {
	Vec3f force = { 0,0,0 };
	force[1] = mass*0.4;
	if (startpoint[1]<=floory+0.01) {
		netforce[1] -= force[1];
		torque += (double)force[1] * sin(TORADIAN(90-thetax));
		if (parent == nullptr)
			netforce = balancedTorque(netforce, targetuplift);
		collideFloor = true;
		return netforce;
	}
	collideFloor = false;
	return netforce;
}
Vec3f LegPhysics::collisionEndWithFloor(Vec3f netforce) {
	Vec3f force = { 0,0,0 };
	force[1]  = mass * 0.4;
	if (endpoint[1] <= floory) {
		netforce[1] += force[1];
		torque -= (double)force[1] * sin(TORADIAN(90 - thetax));
	}
	return netforce;
}
Vec3f LegPhysics::torquefromParent(Vec3f netforce) {
	Vec3f force = { 0,0,0 };
	force[1] = mass*0.1;
	netforce[1] += force[1];
	torque += (double)force[1] * sin(TORADIAN(90 - thetax));
	//cout << torque << "torque2" << endl;
return netforce;
}
void LegPhysics::updateRI() {
	RI = (1 / 3.0)*mass*length*length;
	//cout << "RI:<<" << RI << endl;
}
void LegPhysics::updateRotation(double dt) {
	updateRI();
	omegaAcc = torque/RI;
//	cout << omegaAcc << endl;
	double thetachange = max(min(TODEGREE( omegaX + dt / 1000.0 * (omegaAcc)),4),-4);


	//cout << thetachange << endl;
	double theta =thetax+ thetachange;
	/*if (parent == nullptr) {
		if (theta < -90) {
			return;
		}
	}
	else {
		if (theta > -40) {
			return;
		}
	}*/
	if (endpoint[1]>floory) {

		thetax += thetachange;
		omegaX += dt / 1000.0 * omegaAcc;
	}
	else {
		Vec3f end = { x, (float)(y - length * sin(TORADIAN(theta))), (float)(z + length * cos(TORADIAN(theta))) };
		cout << end[1] << endl;
		if (end[1]>endpoint[1]) {
			thetax += thetachange;
			omegaX += dt / 1000.0 * omegaAcc;
		}
//		pointsToPlot(startpoint, endpoint);

	}

}
void LegPhysics::updateMotion(double dt) {
	x += motion[0];
	y += (min(motion[1],0.024));
	z += motion[2];
}
Vec3f LegPhysics::balancedTorque(Vec3f netforce,float theta) {
	double targetheight = startpoint[1]+length * sin(TORADIAN(theta)); //for standing
	double diffy = targetheight-endpoint[1] ;
	//1.1.8f 50f
	int sign = 1;
	if (thetax < -90)
		sign = -1;
	Vec3f force = { 0.0f, (float)(diffy*kp*mass+ sign*omegaX*kd), 0.0f }; //pid physics brah//ok nice num
	netforce[1] += force[1];
	if (thetax<-90)
		torque -= (double)force[1] * sin(TORADIAN(90 - thetax));
	else
		torque -= (double)force[1] * sin(TORADIAN(90 - thetax));


	return netforce;
}
void LegPhysics::draw()
{

	if (parent == nullptr) {
		startpoint = { x,y,z };

	}
	else {
		startpoint = { parent->endpoint[0],parent->endpoint[1],parent->endpoint[2] };
		x = startpoint[0];
		y = startpoint[1];
		z = startpoint[2];
		netforce = balancedTorque(netforce,targetuplift);


	}

	netforce = collisionStartWithFloor(netforce);
	netforce = collisionEndWithFloor(netforce);
	
	

	if(thetax<-90)
	endpoint = { x,(float)(y-length*sin(TORADIAN(thetax))),(float)(z+ length*cos(TORADIAN(thetax)))};
	else
		endpoint = { x,(float)(y - length * sin(TORADIAN(thetax))),(float)(z + length * cos(TORADIAN(thetax))) };

	pointsToPlot(startpoint, endpoint);
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	// draw the leg

	setAmbientColor(1.0f, 1.0f, 1.0f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(x + xoffset, y + yoffset, z + zoffset);
	glPushMatrix();
	glRotatef(thetax + thetaxOff, 1, 0, 0);
	glPushMatrix();
	glRotatef(thetay + thetayOff, 0, 1, 0);
	glPushMatrix();
	glRotatef(thetaz + thetazOff, 0, 0, 1);
	//glPushMatrix();
	glPushMatrix();

	//glTranslated(-radius/2,-radius/2, -length/2);// draw at center
	drawCylinder(length, radius, radius);

	
	
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	prevendpoint = endpoint;
}
