#include "BallBat.h"
#include "bitmap.h"
#include "global.h"
#include <vector>
using namespace std;
void BallBat::loadTextureSphere(char* fName) {

	int textureWidth, textureHeight;
	unsigned char* image = readBMP(fName, textureWidth, textureHeight);

	GLuint textureObj;

	glGenTextures(1, &textureObj);
	glBindTexture(GL_TEXTURE_2D, textureObj);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glEnable(GL_TEXTURE_2D);
	// Create the sphere
	glPushMatrix();
	glTranslated(1, 0, 0);
	glRotatef(90.0, 1.0, 0.0, 0.0);

	GLUquadric* quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE);
	gluSphere(quadric, 0.2, 30, 30);
	gluDeleteQuadric(quadric);
	glPopMatrix();
	
	// Force the rendering (off-screen)
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void BallBat::loadTextureShield(char* fName) {
	int textureWidth, textureHeight;
	unsigned char* image = readBMP(fName, textureWidth, textureHeight);

	GLuint textureObj;

	glGenTextures(1, &textureObj);
	glBindTexture(GL_TEXTURE_2D, textureObj);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

	glNormal3d(0, 0, -1.0);
	glTexCoord2f(0.0, 1.0); glVertex3d(-1.0, -3.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3d(-1.0, -1.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3d(0.0, -1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3d(0.0, -1.0, 1.0);


	glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

BallBat::BallBat(int x, int y, int z, int w, int h, int L, ModelerView * view) :Component(BODY) {
	float lg_xoffset = 0.82;
	float lg_zoffset = 0.88;
	prevTime = milliseconds(0);
	lp = new LegPhysics(x, y+3, z, 0.1,2.0f, nullptr);
	lpg = new LegPhysics(lp->endpoint[0], lp->endpoint[1], lp->endpoint[2], 0.1, 2, nullptr);
	lpg2 = new LegPhysics(lpg->endpoint[0], lpg->endpoint[1], lpg->endpoint[2], 0.1, 1.0, nullptr);

	lp->nextleg = lpg;
	lp->thetax = -45;
	lp->mass = 20.0;
	lpg->parent = lp;
	lpg2->parent = lpg;
	lpg->mass = 20.0;
	lpg->thetax = -100;

	floory = y - 2;

	grd = new Ground(x-40, floory, z-40 , 80,0.1,80,view);
	// tentacle3 = new Tentacle(tentacle2,tentacle2->end, 0.3, 2);
	this->view = view;
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	this->h = h;
	this->l = L;
	xoffset = 0;//for debug mainly
	yoffset = 0;
	zoffset = 0;
	thetax = 0;
	thetay = 0;
	thetaz = 0;
	thetaxOff = 0;
	thetayOff = 0;
	thetazOff = 0;
	jumped = false;
	leanded = false;
	angle_ring = new Torus(-2, 0, -2.5, 1.5, 0.3, 8, 15);
	//we use pid to control torque for standing 
	lp->gF = 0.1;
	lpg->gF = 0.1;
	lpg->kp = 0.37f;
	lpg->kd = 200;

	lp->kp = 1.3f;
	lp->kd = 540.0f;
	lp->targetuplift = 45;
	lpg->targetuplift = 65;

	lpg->floory = floory;
	lp->floory = floory;
	 
}


static GLfloat lightPosition0[] = { 8, 0, -8, 0 };
static GLfloat lightDiffuse0[] = { 1,1,1,1 };



void BallBat::setup() {
milliseconds ms = duration_cast< milliseconds >(
	system_clock::now().time_since_epoch()
	);
prevTime = ms;
}
void BallBat::leanforward() {
	//if (!leanded) {
		lp->torque = 0.0001f;
		lpg->torque = 0.1f;
		
		lp->targetuplift = 40;
		lpg->targetuplift =70;

	//	leanded = true;
	//}
}
void BallBat::leanbackward() {
	//if (!leanded) {
	lp->torque = -0.0001f;
	lpg->torque = -0.3f;

	//lp->targetuplift = 60;
	lpg->targetuplift = 50;

	//	leanded = true;
	//}
}
void BallBat::leanStraight() {
	if (lp->thetax <-70) {
		lp->torque += 6.0f;
	}

	if (lpg->thetax > -90) {
		lpg->torque -= 4.0f;

	}
	lp->targetuplift = 30;
	lpg->targetuplift = 45;
	leanded = false;

}
void BallBat::jumpAction() {
	 if(!jumped &&  view->leanb){
		if (lp->collideFloor) {
			lp->torque -= 170;
			lpg->torque += 20;
			lp->targetuplift = (lp->targetuplift + 10);
			lpg->targetuplift = (lpg->targetuplift + 7);
		}
		//lp->targetuplift = lp->targetuplift+3;
		//lpg->targetuplift = lpg->targetuplift + 30;
		jumped = true;
	}
	else if(!jumped) {
		/*if (lp->collideFloor) {
		lp->torque -= 2.6f;
		lpg->torque +=2.6f;
		}*/
		if (lp->collideFloor) {
			lp->torque -= 100.6f;
			lpg->torque += 95.6f;
			lp->targetuplift = min(lp->targetuplift + 10, 90);
			lpg->targetuplift = min(lpg->targetuplift + 10, 90);
		}
		//lp->targetuplift = lp->targetuplift+3;
		//lpg->targetuplift = lpg->targetuplift + 30;
		jumped = true;
	}
	
}
void BallBat::calCgVelocity(double dt) {
	 v = (cg-prevCg);
	v *= (1 / dt);
	//cout << "diffy" << v[1] << endl;

}
void BallBat::porjection(double dt) {
	project = true;
	cg = cg + v * dt;
	//lp->motion[0] = v[0] * dt;
	lp->motion[1] = v[1] * dt;
	//lp->motion[2] = v[2] * dt;
//	cout << lp->motion[1] <<"thev"<< v[1]<< endl;


}
void BallBat::airMotion(double dt) {
	lp->motion[0] = v[0] * dt;
	lp->motion[2] = v[2] * dt;

}
void BallBat::endproject() {
	lp->motion[0] = 0;
	//lp->motion[1] = 0;
	lp->motion[2] = 0;
	project = false;
}
void BallBat::gravity(double dt) {
	//v[1] -= 0.1*dt;
}

void BallBat::draw()
{


	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	// draw the body
	milliseconds ms = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch()
		);

	milliseconds dt = ms - prevTime;


//	cout << "detect mouse move" << dt.count()<<","<< view->jump << endl;
	prevTime = ms;
	lp->netforce = { 0,0,0 };
	lp->torque = 0;
	lpg->netforce = { 0,0,0 };
	lpg->torque = 0;
	cg = lpg->endpoint;
	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition0);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightPosition0);
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_GREEN);
	glPushMatrix();
	glTranslated(x + xoffset, y + yoffset, z + zoffset);
	glPushMatrix();
	glRotatef(thetax + thetaxOff, 1, 0, 0);
	glPushMatrix();
	glRotatef(thetay + thetayOff, 0, 1, 0);
	glPushMatrix();
	glRotatef(thetaz + thetazOff, 0, 0, 1);
	glPushMatrix();
	if (view->leanf) {
		leanforward();
	}
	else if (view->leanb) {
		leanbackward();
	}
	else {
		leanStraight();
	}
	if (view->jump) {
		jumpAction();
	}
	else {
		jumped = false;
	}
	//cout << "dd1" << lp->collideFloor << endl;
	if(lp->collideFloor)
	calCgVelocity(dt.count() / 1000.0);
	if (lp->collideFloor && project) {
		endproject();
	}
	else {
		if (!lp->collideFloor&&project) {
			airMotion(dt.count() / 1000.0f);
		}
		if (abs(lp->omegaX) < 0.016 &&lp->collideFloor&&view->jump ) {
			porjection(dt.count() / 1000.0);
			//jumped = true;

			//	cout << "reach"<<lp->collideFloor << endl;
		}
	}
	if (!lp->collideFloor) {
		gravity(dt.count() / 1000.0);

	}

	//cout<<"dd" << lp->collideFloor << endl;
	lp->gravity(dt.count());
	lp->updateMotion(dt.count() / 1000.0);
	lp->draw();
	lp->updateRotation(dt.count());
	lpg->gravity(dt.count());

	lpg->draw();
	lpg->updateRotation(dt.count());
	lpg2->draw();
	grd->draw();
	cout << lp->motion[1] << "motion[1]" << endl;
	//TestComp(canon);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	prevCg = cg;
}
