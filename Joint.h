#pragma once
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include "Component.h"
#include <FL/gl.h>

#include "modelerglobals.h"

struct Joint
{
    int x;
    int y;
    int z;
    float radius;
    Joint(int x, int y, int z, float r, Component* label);
  //  virtual void draw();
};