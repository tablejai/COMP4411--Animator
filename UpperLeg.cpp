#include "UpperLeg.h"
using namespace std;
 UpperLeg::UpperLeg(int x, int y,int z, float r, float L, char* label):Component(UPPERLEG){
	 this->x = x;
	 this->y = y;
	 this->z = z;
	 this->radius = r;
	 this->length = L;
	 this->thetax = 0;
	 joint = new Joint(0,0,0,radius,this);
	 lowerleg = new LowerLeg(0,0,2.91+0.93,r,L,nullptr);
	  for (int i = 0;i < 2;i++) {
		  MetaBall* ptr = new MetaBall(0, 0, i*2+0.4, 1.0f, nullptr);
		 metaballs.push_back(ptr);
	  }
	  xoffset = 0 ;//for debug mainly
	  yoffset = 0 ;
	  zoffset = 0;
	  thetax = 0 ;
	  thetay = 0 ;
	  thetaz = 0 ;
	  thetaxOff = 0;
	  thetayOff = 0;
	  thetazOff = 0;

}
void UpperLeg::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	// draw the leg
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(x+xoffset,y+yoffset,z+zoffset);
	glPushMatrix();
	glRotatef(thetax+thetaxOff,1,0,0);
	glPushMatrix();
	glRotatef(thetay+ thetayOff, 0, 1, 0);
	glPushMatrix();
	glRotatef(thetaz+ thetazOff, 0, 0, 1);
	//glPushMatrix();
 	glPushMatrix();

	drawCylinder(length,radius,radius);
	
	if (VAL(LEVEL_OF_DETAIL) >= 5) 
	for (auto& balls : metaballs) {
		//TestComp(balls);
		balls->draw();
	}
	lowerleg->draw();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}
