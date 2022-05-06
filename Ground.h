#pragma once
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

struct Ground :Component
{
	Ground(int x, int y, int z, int w, int l, int h, ModelerView* view);

	//BallBat(int x, int y, int w, int h, char* label);

	ModelerView* view;
	//body parts
	int w;
	int h;
	int l;
	int x;
	int y;
	int z;

	virtual void draw();

};