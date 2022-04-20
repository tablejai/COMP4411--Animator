#include "canon.h"
using namespace std;
Canon::Canon(int x, int y, int z, float r, float L, char* label) :Component(UPPERLEG) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->radius = r;
	this->length = L;
	this->thetax = 0;
	joint = new Joint(0, 0, 0, radius, this);
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
SmallCanon::SmallCanon(int x, int y, int z, float r, float L, char* label) : Component(UPPERLEG) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->radius = r;
	this->length = L;
	this->thetax = 0;
	joint = new Joint(0, 0, 0, radius, this);
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
void SmallCanon::draw() {
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(x + xoffset, y + yoffset, z + zoffset);
	glPushMatrix();
	glRotatef(thetax + thetaxOff, 1, 0, 0);
	glPushMatrix();
	glRotatef(thetay + thetayOff, 0, 1, 0);
	glPushMatrix();
	glRotatef(thetaz + thetazOff, 0, 0, 1);
	glPushMatrix();

	drawCylinder(length, radius, radius);

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}
void Canon::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	// draw the leg
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(x + xoffset, y + yoffset, z + zoffset);
	glPushMatrix();
	glRotatef(thetax + thetaxOff, 1, 0, 0);
	glPushMatrix();
	if (VAL(ANIMATE) == 1.0) {
		static float dir = 1.0;
		float increment = dir * VAL(HIGHNESS) * 2.0;
		thetayOff += increment;
		if (thetayOff >= 180) {
			dir = -1.0;
		}
		else if (thetayOff <= 0) {
			dir = 1.0;
		}
	}
	else {
		thetayOff = VAL(MOVECANON);
	}
	glRotatef(thetay + thetayOff, 0, 1, 0);
	glPushMatrix();
	glRotatef(thetaz + thetazOff, 0, 0, 1);
	//glPushMatrix();
	glPushMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslated(0, 0 , -radius);
	drawCylinder(radius*3, 2*radius, 2*radius);
	glPopMatrix();
	drawCylinder(length, radius, radius);
	glPushMatrix();
	drawCylinder(length*0.5, 2 * radius, 2 * radius);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}
