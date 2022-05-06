#include "Ground.h"
#include "bitmap.h"
#include "global.h"
#include <vector>
using namespace std;
Ground::Ground(int x, int y, int z, int w, int h, int L, ModelerView * view) :Component(BODY) {
	
	this->view = view;
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	this->h = h;
	this->l = L;



}


void Ground::draw()
{
	setAmbientColor(1, 1, 1);
	setDiffuseColor(1,1,1);
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
	drawBox(w,h,l);
	////glTranslated(-radius/2,-radius/2, -length/2);// draw at center
	//drawCylinder(length, radius, radius);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	// draw the body
	

}
