#include "Spider.h"
#include "bitmap.h"
#include "global.h"
#include <vector>
using namespace std;

void Spider::loadTextureSphere(char* fName) {

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

void Spider::loadTextureShield(char* fName) {
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
Spider::Spider(int x, int y, int z,int w, int h, int L, ModelerView * view):Component(BODY){
	float lg_xoffset = 0.82;
	float lg_zoffset = 0.88;
	head = new Head(x-5, y, z, 1.0, 1.0,1.0, nullptr);
	 ulu_Leg = new UpperLeg(w+x- lg_xoffset,y , z+ L- lg_zoffset, 0.2,3 , nullptr);
	 ulu_Leg->thetax = 20;
	 ulu_Leg->lowerleg->thetax = 69.15;
	 uld_Leg = new UpperLeg(w+x- lg_xoffset, y, z-L+ lg_zoffset, 0.2, 3, nullptr);
	 uld_Leg->thetax = 160;
	 uld_Leg->lowerleg->thetax = -69.15+360;

	 uru_Leg = new UpperLeg(-w+x + lg_xoffset, y, z + L- lg_zoffset, 0.2, 3, nullptr);
	 uru_Leg->thetax = 20;
	 uru_Leg->lowerleg->thetax = 69.15;

	 urd_Leg = new UpperLeg(-w+ x + lg_xoffset, y, z - L+ lg_zoffset, 0.2, 3, nullptr);
	 urd_Leg->thetax = 160;
	 urd_Leg->lowerleg->thetax = -69.15 + 360;
	// metaball = new MetaBall(x, y, z,1,nullptr);
	 canon = new Canon(x, y + 1.0, z+2.23, 0.3, 7, nullptr);
	 canon2 = new Canon(x, y + 1.0, z - 2.23, 0.3, 7, nullptr);
	 canon->thetax = 270;
	 canon->thetay = 270;
	 canon2->thetax = 270;
	 canon2->thetay = 270;
	 tentacle1 = new Tentacle(XYZ{ x + 3.0, y + 1.0, z - 0.0 }, 0.3, 2);
	 tentacle2 = new Tentacle(tentacle1, tentacle1->end, 0.3, 2);

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

 }


static GLfloat lightPosition0[] = { 8, 0, -8, 0 };
static GLfloat lightDiffuse0[]  = { 1,1,1,1 };

void Spider::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	// draw the body
	TestCompOffset(this);

    glLightfv( GL_LIGHT2, GL_POSITION, lightPosition0 );
    glLightfv( GL_LIGHT2, GL_DIFFUSE, lightPosition0 );

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
	head->yoffset = 0;
	head->xoffset = 0;
	head->height = 1.0;
	canon->yoffset = 0;
	canon2->yoffset = 0;
	if (VAL(CHANGE_BODY) == 0)
	{
		
		glScaled(w, h, l);

		drawSphere(1);
		head->thetaz = 270;

	}
	else if (VAL(CHANGE_BODY) == 1)
	{
		vector<vector<double>>Faces[16];
		//int counRect=0;
		float offset = -1.0f;
		#define HEIGHT_HALF h/2.0
		#define WIDTH_HALF w/2.0
		#define LENGTH_HALF l/2.0
		for (int i = 0;i < 6;i++) {
			Faces[0].push_back(vector<double>{ w* cos(i* M_PI / 3.0), HEIGHT_HALF, w* sin(i* M_PI / 3.0) });
			Faces[1].push_back(vector<double>{ w* cos(i* M_PI / 3.0), -HEIGHT_HALF, w* sin(i* M_PI / 3.0)});
		}
		for (int j = 1;j < 6;j++) {
			int i = j + 2;
			Faces[i].push_back(vector<double>{ Faces[0][j - 1][0], -HEIGHT_HALF, Faces[0][j - 1][2] });
			Faces[i].push_back(vector<double>{ Faces[0][j - 1][0], HEIGHT_HALF, Faces[0][j - 1][2] });
			Faces[i].push_back(vector<double>{ Faces[0][j][0], HEIGHT_HALF, Faces[0][j][2] });
			Faces[i].push_back(vector<double>{ Faces[0][j][0], -HEIGHT_HALF, Faces[0][j][2] });
		}
		Faces[2].push_back(vector<double>{ Faces[0][5][0], -HEIGHT_HALF, Faces[0][5][2] });
		Faces[2].push_back(vector<double>{ Faces[1][5][0], HEIGHT_HALF, Faces[1][5][2] });
		Faces[2].push_back(vector<double>{ Faces[0][0][0], HEIGHT_HALF, Faces[0][0][2] });
		Faces[2].push_back(vector<double>{ Faces[1][0][0], -HEIGHT_HALF, Faces[1][0][2] });
		for (int i = 0;i < 6;i++) {
			Faces[8].push_back(vector<double>{ w / 2 * cos(i * M_PI / 3.0), HEIGHT_HALF - offset, w / 2 * sin(i * M_PI / 3.0) });
			Faces[9].push_back(vector<double>{ w / 2 * cos(i * M_PI / 3.0), -HEIGHT_HALF - offset, w / 2 * sin(i * M_PI / 3.0) });
		}
		for (int j = 1;j < 6;j++) {
			int i = j + 10;
			Faces[i].push_back(vector<double>{ Faces[8][j - 1][0], -HEIGHT_HALF - offset, Faces[8][j - 1][2] });
			Faces[i].push_back(vector<double>{ Faces[8][j - 1][0], HEIGHT_HALF - offset, Faces[8][j - 1][2] });
			Faces[i].push_back(vector<double>{ Faces[8][j][0], HEIGHT_HALF - offset, Faces[8][j][2] });
			Faces[i].push_back(vector<double>{ Faces[8][j][0], -HEIGHT_HALF - offset, Faces[8][j][2] });
		}
		Faces[10].push_back(vector<double>{ Faces[8][5][0], -HEIGHT_HALF - offset, Faces[8][5][2] });
		Faces[10].push_back(vector<double>{ Faces[9][5][0], HEIGHT_HALF - offset, Faces[9][5][2] });
		Faces[10].push_back(vector<double>{ Faces[8][0][0], HEIGHT_HALF - offset, Faces[8][0][2] });
		Faces[10].push_back(vector<double>{ Faces[9][0][0], -HEIGHT_HALF - offset, Faces[9][0][2] });


		for (int i = 0;i < 16;i++) {
			if (Faces[i].size() >= 2)
				drawFace(Faces[i]);
		}
		canon->yoffset = HEIGHT_HALF;
		canon2->yoffset = HEIGHT_HALF;
		head->thetaz = 270;

	}
	 if (VAL(CHANGE_HEAD) == 1) {
		head->yoffset = h*2.2;
		head->xoffset = w;
		head->height = 4;
		glPushMatrix();
		glRotatef(270, 1, 0, 0);
		drawCylinder(h * 2.2,0.5,0.5);
		glPopMatrix();
	}
	// loadTextureShield("meme.bmp");
	loadTextureSphere("meme.bmp");

	glPopMatrix();
	//TestComp(head);
	//head->thetax = 90;
	if (VAL(LEVEL_OF_DETAIL) >= 1) 
	head->draw();

	OscillateCompY(ulu_Leg,10);
	OscillateCompY(ulu_Leg->lowerleg, 30);
	OscillateCompY(ulu_Leg->lowerleg->hand, 60);

	OscillateCompY(uld_Leg, 10)
	OscillateCompY(uld_Leg->lowerleg, 30);
	OscillateCompY(uld_Leg->lowerleg->hand, 60);

	
	OscillateCompY(uru_Leg, -10);
	OscillateCompY(uru_Leg->lowerleg, -30);
	OscillateCompY(uru_Leg->lowerleg->hand, -60);


	OscillateCompY(urd_Leg, -10);
	OscillateCompY(urd_Leg->lowerleg, -30);
	OscillateCompY(urd_Leg->lowerleg->hand, -60);


	if (VAL(LEVEL_OF_DETAIL) >= 2) 
	canon->draw();
	if (VAL(LEVEL_OF_DETAIL) >= 2) 
	canon2->draw();
	ulu_Leg->draw();
	uld_Leg->draw();
	uru_Leg->draw();
	urd_Leg->draw();

	tentacle2->follow(XYZ{ VAL(TENTACLE_X_TAR) + tentacle1->start.x, VAL(TENTACLE_Y_TAR) + tentacle1->start.y, VAL(TENTACLE_Z_TAR)+ tentacle1->start.z });
	tentacle2->update();
	if (VAL(LEVEL_OF_DETAIL) >= 3) 
	tentacle2->draw();
	tentacle1->followChild(XYZ{ VAL(TENTACLE_X_TAR), VAL(TENTACLE_Y_TAR), VAL(TENTACLE_Z_TAR) });
	tentacle1->update();
	if (VAL(LEVEL_OF_DETAIL) >= 3) 
	tentacle1->draw();

	//tentacle3->follow(XYZ{VAL(TENTACLE_X_TAR), VAL(TENTACLE_Y_TAR), VAL(TENTACLE_Z_TAR)});
	//tentacle3->update();
	//tentacle3->draw();
	//tentacle2->followParent();
	//tentacle2->update();
	//tentacle2->draw();



	//tentacle3->followParent();
	//tentacle3->update();
	//tentacle3->draw();
	if (VAL(LEVEL_OF_DETAIL) >= 4) 
	angle_ring->draw();
	//TestComp(canon);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}
