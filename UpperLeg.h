#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include "modelerglobals.h"
#include "Joint.h"
#include "LowerLeg.h"
#include "Component.h"
#include "MetaBall.h"
#include "global.h"
#include <vector>
#include <algorithm>

struct UpperLeg: public Component
{
    //float x;
    //float y;
    //float z;
    //float xoffset;//for debug mainly
    //float yoffset;
    //float zoffset;
    //float thetax;
    //float thetay;
    //float thetaz;
    //float thetaxOff;
    //float thetayOff;
    //float thetazOff;
    float length;
    float radius;
    UpperLeg(int x, int y,int z,float r, float L, char* label);
    Joint* joint;
    LowerLeg* lowerleg;
    std::vector<MetaBall*> metaballs;
    virtual void draw();
};