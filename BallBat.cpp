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
	lp = new LegPhysics(x, y+3, z, 0.1,3.0, nullptr);
	lpg = new LegPhysics(lp->endpoint[0], lp->endpoint[1], lp->endpoint[2], 0.1, 2.0, nullptr);
	lp->nextleg = lpg;
	lp->thetax = 120;
	lp->mass = 20.0;
	lpg->parent = lp;
	lpg->mass = 20.0;
	lpg->thetax = 0;
	//ulu_Leg = new UpperLeg(w + x - lg_xoffset, y, z + L - lg_zoffset, 0.2, 3, nullptr);
	//ulu_Leg->thetax = 20;
	//ulu_Leg->lowerleg->thetax = 69.15;
	//uld_Leg = new UpperLeg(w + x - lg_xoffset, y, z - L + lg_zoffset, 0.2, 3, nullptr);
	//uld_Leg->thetax = 160;
	//uld_Leg->lowerleg->thetax = -69.15 + 360;

	//uru_Leg = new UpperLeg(-w + x + lg_xoffset, y, z + L - lg_zoffset, 0.2, 3, nullptr);
	//uru_Leg->thetax = 20;
	//uru_Leg->lowerleg->thetax = 69.15;

	//urd_Leg = new UpperLeg(-w + x + lg_xoffset, y, z - L + lg_zoffset, 0.2, 3, nullptr);
	//urd_Leg->thetax = 160;
	//urd_Leg->lowerleg->thetax = -69.15 + 360;
	//// metaball = new MetaBall(x, y, z,1,nullptr);
	//canon = new Canon(x, y + 1.0, z + 2.23, 0.3, 7, nullptr);
	//canon2 = new Canon(x, y + 1.0, z - 2.23, 0.3, 7, nullptr);
	//canon->thetax = 270;
	//canon->thetay = 270;
	//canon2->thetax = 270;
	//canon2->thetay = 270;
	//tentacle1 = new Tentacle(XYZ{ x + 3.0, y + 1.0, z - 0.0 }, 0.3, 2);
	//tentacle2 = new Tentacle(tentacle1, tentacle1->end, 0.3, 2);
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
	
	angle_ring = new Torus(-2, 0, -2.5, 1.5, 0.3, 8, 15);
	lp->gF = 0.1;
	lpg->gF = 0.1;
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
	lp->gravity(dt.count());

	lp->draw();
	lp->updateRotation(dt.count());
	lpg->gravity(dt.count());

	lpg->draw();
	lpg->updateRotation(dt.count());

	grd->draw();
	//TestComp(canon);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}
