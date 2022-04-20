#pragma once
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
struct SmallCanon : public Component
{

    float length;
    float radius;
    SmallCanon(int x, int y, int z, float r, float L, char* label);
    Joint* joint;
    LowerLeg* lowerleg;
    std::vector<MetaBall*> metaballs;
    virtual void draw();
};
struct Canon : public Component
{
   
    float length;
    float radius;
    Canon(int x, int y, int z, float r, float L, char* label);
    Joint* joint;
    LowerLeg* lowerleg;
    std::vector<MetaBall*> metaballs;
    virtual void draw();
};