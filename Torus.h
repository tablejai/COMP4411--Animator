#pragma once
#include <FL/gl.h>
#include <math.h>

class Torus {
public:
	Torus(double x, double y, double z, double outerRadius, double innerRadius, int numc, int numt) : x{ x }, y{ y }, z{ z }, outerRadius{ outerRadius }, innerRadius{ innerRadius }, numc{ numc }, numt{ numt }{}
	
	double x;
	double y;
	double z;
	double outerRadius;
	double innerRadius;
	int numc;
	int numt;
	void draw();
};
