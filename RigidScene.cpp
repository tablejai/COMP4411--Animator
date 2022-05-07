#include "RigidScene.h"
#include <string>
RigidScene::RigidScene(int x, int y, int z, ModelerView* view) :Component(RIGIDSCENE_){

	this->x - x;
	this-> y = y;
	this->z = z;
	this->floory = -6;
	this->view = view;
	prevTime = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch()
		);
	grd = new Ground(x - 40, floory, z - 40, 80, 0.01, 80, view);
}

void RigidScene::addbody(Rigid*rg) {
	
	bodies.push_back(rg);


}
static GLfloat lightPosition0[] = { 8, 0, -8, 0 };
static GLfloat lightDiffuse0[] = { 1,1,1,1 };

void RigidScene::draw() {
	//cal Force
	simulate = view->simulate;
	milliseconds ms = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch()
		);

	milliseconds dt = ms - prevTime;

	for (Rigid*r : bodies) {
		r->netforce = { 0,0,0 };
		r->acc = { 0,0,0 };
	}
	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition0);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightPosition0);
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_GREEN);
	glPushMatrix();
	glTranslated(x + xoffset, y + yoffset, z + zoffset);
	glPushMatrix();
	glRotatef(thetax + thetaxOff, 1, 0, 0);
	glPushMatrix();
	glRotatef(thetay + thetayOff, 0, 1, 0);
	glPushMatrix();
	glRotatef(thetaz + thetazOff, 0, 0, 1);
	glPushMatrix();
	for (Rigid*r : bodies) {
		//cout << r->x << "," << r->y << "," << r->z << endl;
		if (simulate) {
			for (Rigid*r2 : bodies) {
				if (r2 != r)
					r->netforce += (5 * r->collideForce(*r2));
			}
		}
		//apply gravity
		if (r->y - r->radius>=floory) {
			
			r->netforce[1] -= 3;
		}
		else {
			r->velocity[1] = 1;
			r->netforce[1] +=  3;
		}
		if (r->x - r->radius< -4) {
			r->velocity[0] = 2;
			r->netforce[0] +=3;
		}
		if (r->x + r->radius> 4) {
			r->velocity[0] = -2;

			r->netforce[0] -= 3;

		}
		if (r->z - r->radius< -8) {
			r->velocity[2] = 1;

			r->netforce[2] += 3;
		}
		if (r->z + r->radius> 8) {
			r->velocity[2] = -1;

			r->netforce[2] -= 3;

		}
	}
	////cal acc and v
	for (Rigid*r : bodies) {
		//cout << "(dt.count() / 1000.0)" << (dt.count() / 1000.0) << endl;
		r->acc = r->netforce/r->mass;
		r->velocity += (dt.count() / 1000.0)*r->acc;
		//cout<< r->netforce<<' '<<(dt.count() / 1000.0 )<<" "  << "v"<< r->velocity<<"acc"<< r->acc << endl;
	}
	//update pos

	for (Rigid*r : bodies) {
		cout << r->x << "," << r->y << "," << r->z << endl;
		r->x += (( dt.count() / 1000.0)* r->velocity)[0];
		r->y += ((dt.count() / 1000.0)* r->velocity)[1];
		r->z += ((dt.count() / 1000.0)* r->velocity)[2];
		r->updateBody();
		r->draw();

	}

	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	grd->draw();

	prevTime = ms;


}