#pragma once
#include "Ground.h"
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
#include <chrono>
#include "LegPhysics.h"
using namespace std::chrono;
#include "Tentacle.h"
struct BallBat :Component
{
	BallBat(int x, int y, int z, int w, int l, int h, ModelerView* view);
	//BallBat(int x, int y, int w, int h, char* label);

	ModelerView* view;
	//body parts
	int w;
	int h;
	int l;
	int floory ;
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
	Ground *grd;
	LegPhysics*lp;
	LegPhysics*lpg;

	milliseconds prevTime;
	virtual void draw();
	void setup();
	void loadTextureShield(char * fName);
	void loadTextureSphere(char * fName);
};