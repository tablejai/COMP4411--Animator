#pragma once
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include "modelerglobals.h"
#include "vec.h"
#include "FL/GLU.h"

struct Tentacle {
    XYZ start;
    XYZ end;
    Vec<float> theta = {0,0};
    float length;
    float radius;
    Tentacle* child = nullptr;
    Tentacle* parent = nullptr;

    Tentacle(Tentacle* _parent, XYZ _start, float r, float l) ;
    Tentacle(XYZ _start, float r, float l);

    void drawCylinderWithTwoPts(XYZ a, XYZ b);
    void followChild(XYZ tar);
    void follow(XYZ tar);
    void draw(void);
    void update();
};