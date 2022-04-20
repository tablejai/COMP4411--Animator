#pragma 
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


void drawFace(vector<vector<double>> points);