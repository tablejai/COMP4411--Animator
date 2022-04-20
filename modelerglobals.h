#ifndef _MODELER_GLOBALS_H
#define _MODELER_GLOBALS_H

#include <cmath>

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502
#endif

// This is a list of the controls for the SampleModel
// We'll use these constants to access the values 
// of the controls from the user interface.
struct XYZ {
	double x;
	double y;
	double z;
};
enum SampleModelControls
{ 
	LEVEL_OF_DETAIL, XPOS, YPOS, ZPOS, XTHETA,YTHETA, ZTHETA, OSCILLATEY, HEIGHT, ROTATE, RESOLUTIONMETABALL, LSYSTEMDISPLAY,LSYSTEMOBJECTTYPE,
	LSYSTEMDVALUE,
	LSYSTEMINITIALANGLE,
	FRAME, CHANGE_LEG, CHANGE_HEAD, CHANGE_BODY,
	LSYSTEMITER, MOVECANON, ANIMATE, HIGHNESS,TENTACLE_X_TAR, TENTACLE_Y_TAR, TENTACLE_Z_TAR, TENTACLE_ANG_CONSTRAINT, NUMCONTROLS

};

// Colors
#define COLOR_RED		1.0f, 0.0f, 0.0f
#define COLOR_GREEN		0.0f, 1.0f, 0.0f
#define COLOR_BLUE		0.0f, 0.0f, 1.0f

// We'll be getting the instance of the application a lot; 
// might as well have it as a macro.
#define VAL(x) (ModelerApplication::Instance()->GetControlValue(x))


/*
 * Stuff below are from global.h before
*/
#include <vector>
using namespace std;
#define TestCompOffset(Component)\
Component->xoffset = VAL(XPOS);\
Component->yoffset = VAL(YPOS);\
Component->zoffset = VAL(ZPOS);\
Component->thetaxOff = VAL(XTHETA);\
Component->thetayOff = VAL(YTHETA);\
Component->thetazOff = VAL(ZTHETA);
#define TestComp(Component)\
Component->x = VAL(XPOS);\
Component->y = VAL(YPOS);\
Component->z = VAL(ZPOS);\
Component->thetax = VAL(XTHETA);\
Component->thetay = VAL(YTHETA);\
Component->thetaz = VAL(ZTHETA);
#define OscillateCompX(Component,offset)\
Component->thetaxOff = sin(VAL(OSCILLATEX)/4.0)/2*offset;
#define OscillateCompY(Component,offset)\
Component->thetayOff = sin(VAL(OSCILLATEY)/4.0)/2*offset;

#define  GeneralDraw(Color,Code)\
setAmbientColor(.1f, .1f, .1f);\
setDiffuseColor(Color); \
glPushMatrix(); \
glTranslated(x + xoffset, y + yoffset, z + zoffset); \
glPushMatrix(); \
glRotatef(thetax + thetaxOff, 1, 0, 0); \
glPushMatrix();  \
glRotatef(thetay + thetayOff, 0, 1, 0); \
glPushMatrix();  \
glRotatef(thetaz + thetazOff, 0, 0, 1); \
glPushMatrix();  \
Code              \
glPopMatrix(); \
glPopMatrix(); \
glPopMatrix(); \
glPopMatrix(); \
glPopMatrix();


static void drawFace(vector<vector<double>> points) {
    vector<double> pt1 = points[0];

    vector<double> pt2 = points[1];
#define mid(a,b) (a+b)/2.0
    vector<double> mid = { mid(pt1[0],pt2[0]),mid(pt1[1],pt2[1]),mid(pt1[2],pt2[2]) };
    for (int i = 0; i < points.size(); i++) {
        vector<double> next;
        if (i + 1 >= points.size()) {
            next = points[0];
        }
        else {
            next = points[i + 1];
        }
        vector<double> pt = points[i];
        drawTriangle(pt[0], pt[1], pt[2], mid[0], mid[1], mid[2], next[0], next[1], next[2]);
    }


}
#endif