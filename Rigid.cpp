//#include "Rigid.h"
//#include "bitmap.h"
//#include "global.h"
//#include <vector>
//using namespace std;
//
//
//void Rigid::draw()
//{
//
//
//	// This call takes care of a lot of the nasty projection 
//	// matrix stuff.  Unless you want to fudge directly with the 
//	// projection matrix, don't bother with this ...
//	// draw the body
//	milliseconds ms = duration_cast< milliseconds >(
//		system_clock::now().time_since_epoch()
//		);
//
//	milliseconds dt = ms - prevTime;
//
//
//	//	cout << "detect mouse move" << dt.count()<<","<< view->jump << endl;
//	prevTime = ms;
//	lp->netforce = { 0,0,0 };
//	lp->torque = 0;
//	lpg->netforce = { 0,0,0 };
//	lpg->torque = 0;	lp2->netforce = { 0,0,0 };
//	lp2->torque = 0;
//	lpg2->netforce = { 0,0,0 };
//	lpg2->torque = 0;
//	cg = lpg->endpoint;
//	cg2 = lpg2->endpoint;
//
//	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition0);
//	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightPosition0);
//	setAmbientColor(.1f, .1f, .1f);
//	setDiffuseColor(COLOR_GREEN);
//	glPushMatrix();
//	glTranslated(x + xoffset, y + yoffset, z + zoffset);
//	glPushMatrix();
//	glRotatef(thetax + thetaxOff, 1, 0, 0);
//	glPushMatrix();
//	glRotatef(thetay + thetayOff, 0, 1, 0);
//	glPushMatrix();
//	glRotatef(thetaz + thetazOff, 0, 0, 1);
//	glPushMatrix();
//
//	glPopMatrix();
//
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	glPopMatrix();
//	prevCg = cg;
//	prevCg2 = cg2;
//}
