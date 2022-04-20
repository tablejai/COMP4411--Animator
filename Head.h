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

struct Head : public Component
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
    float width;
    float height;
    Head(int x, int y, int z, float r, float L,float H, char* label);
    Joint* joint;
    std::vector<MetaBall*> metaballs;
    virtual void draw();
};