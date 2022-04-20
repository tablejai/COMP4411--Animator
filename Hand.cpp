#include "Hand.h"
Hand::Hand(int x, int y, int z, float r, float L, char* label) :Component(HAND) {
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

void Hand::draw()
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
	glRotatef(thetay + thetayOff, 0, 1, 0);
	glPushMatrix();
	glRotatef(thetaz + thetazOff, 0, 0, 1);
	//glPushMatrix();
	glPushMatrix();
	if (VAL(CHANGE_LEG) == 0) {
		drawCylinder(length, radius, radius);
		//hand->draw();

	}
	else {
		glPushMatrix();
		float size = length / pow(2, 1 / 3.0);
		glTranslated(-size, -size, -size);
		drawBox(size*2, size*2, size*2);
		glPopMatrix();
		//hand->draw();

	}
	////glTranslated(-radius/2,-radius/2, -length/2);// draw at center
	//drawCylinder(length, radius, radius);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}
