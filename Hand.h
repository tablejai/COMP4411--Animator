#pragma once
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include "modelerglobals.h"
#include "Joint.h"
#include "Component.h"
struct Hand : public Component
{
    float x;
    float y;
    float z;
    float xoffset;//for debug mainly
    float yoffset;
    float zoffset;
    float thetax;
    float thetay;
    float thetaz;
    float thetaxOff;
    float thetayOff;
    float thetazOff;
    float length;
    float radius;
    Hand(int x, int y, int z, float r, float L, char* label);
    Joint* joint;
    virtual void draw();
};