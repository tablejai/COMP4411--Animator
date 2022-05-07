#pragma once
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include "Spider.h"
#include <FL/gl.h>
#include "modelerglobals.h"
#include "BallBat.h"
#include "RigidScene.h"
typedef enum Mode {
	PHYSICS,
	NONPHYSICS,
	RIGIDMODE
};
struct SpiderModel : public ModelerView
{
    SpiderModel(int x, int y, int w, int h, char* label);
	BallBat*ballbat;
    Spider* spider;
	RigidScene* rigidScene;
	Mode mode ;
	Mode prevMode;
    virtual void draw();
};