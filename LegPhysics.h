#pragma once
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include "modelerglobals.h"
#include "Joint.h"
#include "Component.h"
#include "Hand.h"
#include "vec.h"
struct LegPhysics : public Component
{
	//float x;
	//float y;
	//float z;
	//float xoffset;//for debug mainly
	//float yoffset;
	//float zoffset;
	//float thetax;
	//float thetay;
	//float thetaz;
	//float thetaxOff;
	//float thetayOff;
	//float thetazOff;
	float length;
	float radius;
	float floory;
	float gF;
	float mass;
	float RI;//rotational intertia
	float omegaAcc;
	double torque;
	
	LegPhysics(int x, int y, int z, float r, float L, char* label);
	Hand* hand;
	Vec3f motion;
	Vec3f netforce;
	double omegaX;
	Vec3f startpoint;
	Vec3f endpoint;
	Vec3f prevendpoint;

	LegPhysics* parent;
	void updateRI();
	void updateRotation();
	LegPhysics* nextleg;
	void updateRotation(double dt);
	Vec3f collisionStartWithFloor(Vec3f netforce);
	Vec3f collisionEndWithFloor(Vec3f netforce);
	Vec3f torquefromParent(Vec3f netforce);
	Vec3f balancedTorque(Vec3f netforce);

	void balancedtorque();
	void pointsToPlot(Vec3f, Vec3f);
	void gravity(double dt);
	virtual void draw();
};