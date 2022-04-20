#include "Joint.h"
Joint::Joint(int x, int y, int z, float r, Component* label) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->radius = r;
}
//}
//void Joint::draw()
//{
//	// This call takes care of a lot of the nasty projection 
//	// matrix stuff.  Unless you want to fudge directly with the 
//	// projection matrix, don't bother with this ...
//	// draw the leg
//	setAmbientColor(.1f, .1f, .1f);
//	setDiffuseColor(COLOR_RED);
//	glPushMatrix();
//	glTranslated(x, y, z);
//	glPushMatrix();
//	drawSphere(radius);
//	glPopMatrix();
//	glPopMatrix();
//}
