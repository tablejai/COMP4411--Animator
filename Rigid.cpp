#include "Rigid.h"
#include "bitmap.h"
#include "global.h"
#include <vector>
#include <string>
using namespace std;

 Rigid::Rigid(float x, float y, float z, float r,string shape, ModelerView* view):Component(RIGID) {
	if (shape=="Sphere"){
		points.push_back({x,y,z});
	}
	else if (shape == "Hydrogen") {
		points.push_back({ x+r/2.0f,y+r/2.0f,z+r/2.0f});
		points.push_back({ x-r/2.0f,y-r/2.0f,z-r/2.0f});


	}
	this->x = x;
	this->y = y;
	this->z = z;
	this->shape = shape; 
	radius = r;
	this->velocity = { 0,0,0 };
	this->acc = { 0,0,0 };
	this->mass = 2.0;
}

void Rigid::setup() {



}
bool Rigid::collisionDetect( Rigid r2) {

	for (Vec3f pt : this->points) {
		for (Vec3f pt2 : r2.points)
		{
			if ((pt-pt2).length()<= this->radius+r2.radius) {
				return true;
			}
		}
	}
}


Vec3f Rigid::collideForce(Rigid r2) {
	const double force =2;
	Vec3f net = { 0,0,0 };
	for (Vec3f pt : this->points) {
		for (Vec3f pt2 : r2.points)
		{
			if(pt!=pt2)
			if ((pt - pt2).length() <= this->radius + r2.radius) {
				Vec3f getNorm = (pt - pt2);
				getNorm.normalize();
				net += (force * getNorm) / ((pt - pt2).length()*(pt - pt2).length());
			}
		}
	}
	return net;
}
void Rigid::updateBody() {
	if (shape == "Sphere") {
		points[0][0] = x;
		points[0][1] = y;
		points[0][2] = z;

	}
	else if (shape == "Hydrogen") {
		points[0][0] = x-radius;
		points[0][1] = y-radius;
		points[0][2] = z-radius;
		points[1][0] = x + radius;
		points[1][1] = y + radius;
		points[1][2] = z + radius;
	}
}
void Rigid::draw()
{

	setAmbientColor(.1f, .1f, .1f);
	glPushMatrix();
	glTranslated(x + xoffset, y + yoffset, z + zoffset);
	glPushMatrix();
	glRotatef(thetax + thetaxOff, 1, 0, 0);
	glPushMatrix();
	glRotatef(thetay + thetayOff, 0, 1, 0);
	glPushMatrix();
	glRotatef(thetaz + thetazOff, 0, 0, 1);
	//glPushMatrix();
	glPushMatrix();
	if (shape=="Sphere") {
		setDiffuseColor(COLOR_RED);

		glScaled(radius, radius, radius);
		drawSphere(1);
	}
	else if (shape == "Hydrogen") {
		setDiffuseColor(COLOR_BLUE);

		glScaled(radius, radius, radius);

		glPushMatrix();
		glTranslated(-radius,  - radius,  - radius );
		drawSphere(1);

		glPopMatrix();

		glPushMatrix();
		glTranslated(+ radius, + radius , + radius );
		drawSphere(1);

		glPopMatrix();

	}
	
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	
}
