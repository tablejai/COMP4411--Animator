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
	bool project;
	bool project2;
	//body parts
	int w;
	int h;
	int l;
	int floory ;
	double oldx;
	double oldy;
	double oldz;
	Head* h1;
	Head* h2;

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
	LegPhysics* lp2;
	LegPhysics*lpg2;
	Vec3f cg;
	Vec3f prevCg;
	Vec3f cg2;
	Vec3f prevCg2;
	Vec3f v2;
	Vec3f v;
	bool jumped;
	bool leanded;
	milliseconds prevTime;
	void calCgVelocity(double dt);
	void jumpAction();
	//void leanforward(LegPhysics*lp, LegPhysics*lpg);
	void leanStraight(LegPhysics*lp, LegPhysics*lpg);
	void porjection(LegPhysics*lg, LegPhysics*lpg, double dt);
	void projection2(double dt);
	void endproject(LegPhysics*lg, LegPhysics*lpg);
	void airMotion(LegPhysics*lg, LegPhysics*lpg, double dt);
	void leanbackward(LegPhysics*lp, LegPhysics*lpg);
	void gravity(double dt);
	void jumpAction(LegPhysics*lp, LegPhysics*lpg);

	virtual void draw();
	void setup();
	void leanforward(LegPhysics*lp, LegPhysics*lpg);
	void loadTextureShield(char * fName);
	void loadTextureSphere(char * fName);
	void calCgVelocity2(double dt);
};