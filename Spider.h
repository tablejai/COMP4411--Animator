#pragma once
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include "MetaBall.h"
#include "UpperLeg.h"
#include <FL/gl.h>
#include "FL/GLU.h"
#include "global.h"
#include "modelerglobals.h"
#include "canon.h"
#include "Head.h"
#include "Torus.h"
#include "GL/gl.h"
#include "Tentacle.h"

struct Spider:Component
{
    Spider(int x, int y,int z, int w,int l,int h, ModelerView* view);
    ModelerView* view;
    //body parts
    int w;
    int h;
    int l;
  
    double oldx;
    double oldy;
    double oldz;
    UpperLeg* ulu_Leg;
    UpperLeg* uld_Leg;
    UpperLeg* uru_Leg;
    UpperLeg* urd_Leg;
    MetaBall* metaball;
    Canon* canon;
    Canon* canon2;
    Head* head;
    Torus* angle_ring;
    Tentacle* tentacle1;
    Tentacle* tentacle2;
    Tentacle* tentacle3;
    

    virtual void draw();
    void loadTextureShield(char * fName);
    void loadTextureSphere(char * fName);
};