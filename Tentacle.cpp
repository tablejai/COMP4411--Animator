#include "Tentacle.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

#define M_PI 3.141592653589793238462643383279502
#define MAX(x,y) (((x) >= (y))? (x): (y))
#define MIN(x,y) (((x) <= (y))? (x): (y))
#define CLAMP(x,upper, lower) MAX(upper,MIN(lower, x))

Tentacle::Tentacle(Tentacle* _parent, XYZ _start, float r, float l) {
	parent = _parent;
	parent->child = this;
	start = _start;
	radius = r;
	length = l;

	update();
}

static void cross(Vec3f vec1, Vec3f vec2, Vec3f& crossProduct)
{
	crossProduct[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	crossProduct[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	crossProduct[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

static float dot(Vec3f vec1, Vec3f vec2) {
	return vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2];
}

void Tentacle::drawCylinderWithTwoPts(XYZ a, XYZ b) {
	Vec3f z = { 0,0,1 };
	Vec3f p = {(float)(a.x - b.x), (float)(a.y - b.y), (float)(a.z - b.z) };
	Vec3f t;
	cross(z, p, t);

	double angle = 180 / M_PI * acos(dot(z,p)/p.length())+180;
	
	glPushMatrix();
	glTranslated(start.x, start.y, start.z);
	glPushMatrix();
	glRotated(angle, t[0], t[1], t[2]);
	glPushMatrix();


	GLUquadric* quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricOrientation(quadric, GLU_OUTSIDE);
	gluCylinder(quadric ,radius, radius, p.length(), 50, 50);

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


}

Tentacle::Tentacle(XYZ _start, float r, float l) {
	start = _start;
	radius = r;
	length = l;
	follow(XYZ{VAL(TENTACLE_X_TAR), VAL(TENTACLE_Y_TAR), VAL(TENTACLE_Z_TAR)});
	update();
}

void Tentacle::followChild(XYZ tar) {


	XYZ dir = { tar.x - start.x,tar.y - start.y,tar.z - start.z };
	theta[1] = atan2(dir.z, dir.x);
	float x = sqrt(tar.x * tar.x + tar.z * tar.z);
	float l1 = length;
	float l2 = this->child->length;
	float theta2 = this->child->theta[0];
	theta[0] = (-l2*sin(theta2)*x+(l1+l2*cos(theta2))*dir.y) / (-l2 * sin(theta2) *dir.y+ (l1 + l2 * cos(theta2)) * dir.x)/180*3.1415+0.01;
	if (std::isnan(theta[0])) {
		theta[0] = 0;
	}

}

void Tentacle::follow(XYZ tar) {
	XYZ dir = { tar.x - start.x,tar.y - start.y,tar.z - start.z };
	theta[1] = atan2(dir.z,dir.x);

	float x = sqrt(tar.x*tar.x+ tar.z*tar.z);
	if (parent != nullptr) {
	theta[0] =  CLAMP(acosf((x* x + tar.y*tar.y-length*length-pow(parent->length,2))/2/(parent->length)/(length)),0.0, M_PI)+2* 3.1415;
		if (std::isnan(theta[0])) {
			theta[0] = 0;
		}
	}

};

void Tentacle::draw() {
	setAmbientColor(.3f, .3f, .3f);
	setDiffuseColor(COLOR_BLUE);
	drawCylinderWithTwoPts(start, end);
}

void Tentacle::update() {
	// TODO: Check the angles
	if(parent!=nullptr)
	start = this->parent->end;
	float dx = length * cos(theta[0]);
	float dy = length * sin(theta[0]);
	float dz = length * sin(theta[1]);
	end = XYZ{ start.x + dx, start.y + dy, start.z + dz };
}