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


	lp = new LegPhysics(x+1, y+3, z, 0.1,2.0f, nullptr);
	lpg = new LegPhysics(lp->endpoint[0], lp->endpoint[1], lp->endpoint[2], 0.1, 2, nullptr);
	lp2 = new LegPhysics(x, y + 5, z+1, 0.1, 2.0f, nullptr);
	lpg2 = new LegPhysics(lp2->endpoint[0], lp2->endpoint[1], lp2->endpoint[2], 0.1, 2, nullptr);
	h1 = new Head(lp->endpoint[0], lp->endpoint[1], lp->endpoint[2],1,1,1,nullptr);
	h2 = new Head(lp2->endpoint[0], lp2->endpoint[1], lp2->endpoint[2],1, 1, 1, nullptr);
	lp->nextleg = lpg;
	lp->thetax = -45;
	lp->mass = 20.0;
	lp2->nextleg = lpg;
	lp2->thetax = -45;
	lp2->mass = 20.0;
	lpg2->parent = lp2;
	lpg2->mass = 20;
	lpg2->thetax = -100;
	lpg->parent = lp;
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
	lp2->gF = 0.1;
	lpg2->gF = 0.1;
	lpg2->kp = 0.37f;
	lpg2->kd = 200;

	lp2->kp = 1.3f;
	lp2->kd = 540.0f;
	lp2->targetuplift = 45;
	lpg2->targetuplift = 65;

	lpg2->floory = floory;
	lp2->floory = floory;
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
void BallBat::leanforward(LegPhysics*lp, LegPhysics*lpg) {
	//if (!leanded) {
	if (lp->collideFloor) {
		lp->torque = 0.0001f;
		lpg->torque = 0.1f;

		lp->targetuplift = 50;
		lpg->targetuplift = 70;
	}
	//	leanded = true;
	//}
}
void BallBat::leanbackward(LegPhysics*lp, LegPhysics*lpg) {
	//if (!leanded) {
	if (lp->collideFloor) {

		lp->torque = -0.0001f;
		lpg->torque = -0.3f;

		//lp->targetuplift = 60;
		lpg->targetuplift = 50;
	}
	//	leanded = true;
	//}
}
void BallBat::leanStraight(LegPhysics*lp, LegPhysics*lpg) {
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
void BallBat::jumpAction(LegPhysics*lpin,LegPhysics*lping) {
	 if( view->leanb){
		if (lpin->collideFloor) {
			lpin->torque -= 170;
			lping->torque += 20;
			lpin->targetuplift = (lpin->targetuplift + 18);
			lping->targetuplift = (lping->targetuplift + 7);
		}
		//lpin->targetuplift = lpin->targetuplift+3;
		//lping->targetuplift = lping->targetuplift + 30;
	}
	 else  {
	//	 cout << "jping" << endl;

		 if (lpin->collideFloor) {
			 if (lpin->thetax >= -30)
				 lpin->torque -= 100;
				 lping->torque += 300;
			 lpin->targetuplift = min(lpin->targetuplift + 10, 90);
			 lping->targetuplift = min(lping->targetuplift + 10, 90);

			 //lpin->targetuplift = lpin->targetuplift+3;
			 //lping->targetuplift = lping->targetuplift + 30;
		 }
	 }
	
}
void BallBat::calCgVelocity(double dt) {
	 v = (cg-prevCg);
	v *= (1 / dt);
	//cout << "diffy" << v[1] << endl;

}
void BallBat::calCgVelocity2(double dt) {
	v2 = (cg2 - prevCg2);
	v2 *= (1 / dt);
	//cout << "diffy" << v[1] << endl;

}
void BallBat::porjection(LegPhysics*lp, LegPhysics*lpg,double dt) {
	project = true;
	cg = cg + v * dt;
	//lp->motion[0] = v[0] * dt;
	//lp->motion[2] = v[2] * dt;

	lp->motion[1] = v[1] * dt;
	//lp->motion[2] = v[2] * dt;
//	cout << lp->motion[1] <<"thev"<< v[1]<< endl;


}
void BallBat::projection2( double dt) {
	project2 = true;
	cg2= cg2 + v2 * dt;
	//lp2->motion[2] = v[2] * dt;
	lp2->motion[1] = v2[1] * dt;
}
void BallBat::airMotion(LegPhysics*lp, LegPhysics*lpg,double dt) {
	lp->motion[0] = v[0] * dt;
	lp->motion[2] = v[2] * dt;	


}
void BallBat::endproject(LegPhysics*l,LegPhysics*lg) {
	l->motion[0] = 0;
	//l->motion[1] = 0;
	l->motion[2] = 0;	
	if(l==lp)
		project = false;
	else 
		project2 = false;
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
	lpg->torque = 0;	lp2->netforce = { 0,0,0 };
	lp2->torque = 0;
	lpg2->netforce = { 0,0,0 };
	lpg2->torque = 0;
	cg = lpg->endpoint;
	cg2 = lpg2->endpoint;
	
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
	if (view->leanf  ) {
	
		leanforward(lp,lpg);

		leanforward(lp2, lpg2);

	}
	else if (view->leanb) {
		leanbackward(lp,lpg);

		leanbackward(lp2, lpg2);
	}
	else {
		leanStraight(lp, lpg);
		leanStraight(lp2, lpg2);

	}
	if (view->jump) {
		if (!jumped) {
			jumpAction(lp, lpg);
			jumpAction(lp2, lpg2);
			jumped = true;
		}
	}
	else {
		jumped = false;
	}
	//cout << "dd1" << lp->collideFloor << endl;
	if(lp->collideFloor)
	calCgVelocity(dt.count() / 1000.0);
	if (!lp->collideFloor&&project) {
		airMotion(lp, lpg, dt.count() / 1000.0f);
	}
	if ((lp->collideFloor||lp->thetax>0)&&lp->motion[1]<0 && project) {
		endproject(lp,lpg);
	}
	else {
		
		if (abs(lp->omegaX) < 0.016 &&lp->collideFloor&&view->jump ) {
			porjection(lp, lpg,dt.count() / 1000.0);
			//jumped = true;

			//	cout << "reach"<<lp->collideFloor << endl;
		}
	}

	if (lp2->collideFloor)
		calCgVelocity2(dt.count() / 1000.0);
	if (!lp2->collideFloor&&project2) {
		airMotion(lp2, lpg2, dt.count() / 1000.0f);
	}
	if ((lp2->collideFloor || lp2->thetax>0) && lp2->motion[1]<=0 && project2) {
			endproject(lp2, lpg2);
		}
		else {
			
			if (abs(lp2->omegaX) < 0.016 &&lp2->collideFloor&&view->jump) {
				projection2( dt.count() / 1000.0);
				//jumped = true;

				//	cout << "reach"<<lp->collideFloor << endl;
			}
		}
	

	//cout<<"dd" << lp->collideFloor << endl;
	lp->gravity(dt.count());
	lp->updateMotion(dt.count() / 1000.0);
	lp->standUpWhenFall();
	lp->draw();
	
	lp->updateRotation(dt.count());
	lpg->gravity(dt.count());

	lpg->draw();
	lpg->updateRotation(dt.count());
	lp2->gravity(dt.count());
	lp2->updateMotion(dt.count() / 1000.0);
	lp2->standUpWhenFall();
	lp2->draw();
	
	lp2->updateRotation(dt.count());
	lpg2->gravity(dt.count());

	lpg2->draw();
	lpg2->updateRotation(dt.count());
	grd->draw();
	//h1->x = lpg->endpoint[0];
	//h1->y = lpg->endpoint[1];
	//h1->z = lpg->endpoint[2];
	//h2->x = lpg2->endpoint[0];
	//h2->y = lpg2->endpoint[1];
	//h2->z = lpg2->endpoint[2];
	//h1->draw();
	//h2->draw();
	//cout << lp->motion[1] << "motion[1]" << endl;
	//TestComp(canon);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	prevCg = cg;
	prevCg2 = cg2;
}
