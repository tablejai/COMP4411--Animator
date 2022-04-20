#include "Head.h"
using namespace std;
 Head:: Head(int x, int y, int z, float w, float L, float H, char* label) :Component(HEAD) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->width = w;
	this->length = L;
	this->thetax = 0;
	this->height = H;
	for (int i = 0;i < 2;i++) {
		MetaBall* ptr = new MetaBall(0, 0, i * 2 + 0.4, 1.0f, nullptr);
		metaballs.push_back(ptr);
	}
	xoffset = 0;//for debug mainly
	yoffset = 0;
	zoffset = 0;
	thetax = 0;
	thetay = 0;
	thetaz = 0;
	thetaxOff = 0;
	thetayOff = 0;
	thetazOff = 0;

}




void  Head::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	// draw the leg
#define HEIGHT_HALF height/2
#define WIDTH_HALF width/2
#define LENGTH_HALF length/2

	int count = 6;
	vector<vector<double>>Faces[16];
	//int counRect=0;
	float offset = 0.8f;
	for (int i = 0;i < 6;i++) {
		Faces[0].push_back(vector<double>{ width* cos(i* M_PI / 3.0), HEIGHT_HALF, width* sin(i* M_PI / 3.0) });
		Faces[1].push_back(vector<double>{ width* cos(i* M_PI / 3.0), -HEIGHT_HALF, width* sin(i* M_PI / 3.0)});
	}

	for (int j = 1;j < 6;j++) {
		int i = j + 2;
		Faces[i].push_back(vector<double>{ Faces[0][j- 1][0], -HEIGHT_HALF, Faces[0][j - 1][2] });
		Faces[i].push_back(vector<double>{ Faces[0][j - 1][0], HEIGHT_HALF, Faces[0][j - 1][2] });
		Faces[i].push_back(vector<double>{ Faces[0][j][0], HEIGHT_HALF, Faces[0][j][2] });
		Faces[i].push_back(vector<double>{ Faces[0][j][0], -HEIGHT_HALF, Faces[0][j][2] });
	}
	Faces[2].push_back(vector<double>{ Faces[0][5][0], -HEIGHT_HALF, Faces[0][5][2] });
	Faces[2].push_back(vector<double>{ Faces[1][5][0], HEIGHT_HALF, Faces[1][5][2] });
	Faces[2].push_back(vector<double>{ Faces[0][0][0], HEIGHT_HALF, Faces[0][0][2] });
	Faces[2].push_back(vector<double>{ Faces[1][0][0], -HEIGHT_HALF, Faces[1][0][2] });

	for (int i = 0;i < 6;i++) {
		Faces[8].push_back(vector<double>{ width/2* cos(i* M_PI / 3.0), HEIGHT_HALF- offset, width/2* sin(i* M_PI / 3.0) });
		Faces[9].push_back(vector<double>{ width/2* cos(i* M_PI / 3.0), -HEIGHT_HALF-offset, width/2* sin(i* M_PI / 3.0) });
	}
	for (int j = 1;j < 6;j++) {
		int i = j + 10;
		Faces[i].push_back(vector<double>{ Faces[8][j - 1][0], -HEIGHT_HALF-offset, Faces[8][j - 1][2] });
		Faces[i].push_back(vector<double>{ Faces[8][j - 1][0], HEIGHT_HALF - offset, Faces[8][j - 1][2] });
		Faces[i].push_back(vector<double>{ Faces[8][j][0], HEIGHT_HALF - offset, Faces[8][j][2] });
		Faces[i].push_back(vector<double>{ Faces[8][j][0], -HEIGHT_HALF - offset, Faces[8][j][2] });
	}
	Faces[10].push_back(vector<double>{ Faces[8][5][0], -HEIGHT_HALF-offset, Faces[8][5][2] });
	Faces[10].push_back(vector<double>{ Faces[9][5][0], HEIGHT_HALF - offset, Faces[9][5][2] });
	Faces[10].push_back(vector<double>{ Faces[8][0][0], HEIGHT_HALF - offset, Faces[8][0][2] });
	Faces[10].push_back(vector<double>{ Faces[9][0][0], -HEIGHT_HALF - offset, Faces[9][0][2] });
	

	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(x + xoffset, y + yoffset, z + zoffset);
	glPushMatrix();
	glRotatef(thetax + thetaxOff, 1, 0, 0);
	glPushMatrix();
	glRotatef(thetay + thetayOff, 0, 1, 0);
	glPushMatrix();
	static float highness_dir = 1.0;
	thetazOff += (highness_dir * VAL(HIGHNESS) * 2.0);
	if (thetazOff >= 10) {
		highness_dir = -1.0;
	}
	else if (thetazOff <= -10) {
		highness_dir = 1.0;
	}
	glRotatef(thetaz + thetazOff, 0, 0, 1);
	glPushMatrix();

	for (int i = 0;i <16;i++) {
		if (Faces[i].size() >= 2)
			drawFace(Faces[i]);
	}

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}
