#pragma once
#pragma once
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
#include "Tentacle.h"
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
#include "Rigid.h"
#include "Tentacle.h"
struct RigidScene:Component
{
	//Rigid(int x, int y, int z, int w, int l, int h, ModelerView* view);
	RigidScene(int x, int y, int z, ModelerView* view);

	//Rigid(int x, int y, int w, int h, char* label);
	bool simulate;
	ModelerView* view;
	float floory;
	vector<Rigid*> bodies;
	float gf = 0.1;
	bool collisionDetect();
	milliseconds prevTime;
	Vec3f collideForce();
	void updateBody();
	void gravity();
	void addbody(Rigid*rg) ;
	Ground *grd;

	virtual void draw();
	//void setup();

};