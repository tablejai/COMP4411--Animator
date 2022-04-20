#pragma once
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include "Spider.h"
#include <FL/gl.h>
#include "modelerglobals.h"
struct SpiderModel : public ModelerView
{
    SpiderModel(int x, int y, int w, int h, char* label);
    Spider* spider;
    virtual void draw();
};