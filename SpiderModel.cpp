#include "SpiderModel.h"
#include "Rigid.h"
SpiderModel:: SpiderModel(int x, int y, int w, int h, char* label): ModelerView(x, y, w, h, label) {
	
	spider = new Spider(0, 0,0, 4, 2, 2, this);
	ballbat =   new BallBat(0, 0, 0, 4, 2, 2, this);
	rigidScene = new RigidScene(0, 0, 0,this);
	for (float i = -4; i < 4;i+=0.4) {
		Rigid*r = new Rigid(i, 10, 1, 0.2, "Sphere", this);
		Rigid*r2 = new Rigid(i, 10, 1, 0.4, "Hydrogen", this);

		r->velocity = { (float)(rand() % 6 - 3),(float)(rand() % 6 - 3),rand() % 6 - 3.0f };
		r2->velocity = { (float)(rand() % 6 - 3),(float)(rand() % 6 - 3),rand() % 6 - 3.0f };

		rigidScene->addbody(r);
		rigidScene->addbody(r2);

	}
	
	mode = NONPHYSICS;
}
void SpiderModel::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	ModelerView::draw();
	mode =(Mode)(int)VAL(Physically_Based_Animation);
	if (mode == NONPHYSICS)
		spider->draw();
	else if(mode==PHYSICS)
	{
		if (prevMode != mode)
			ballbat->setup();
		ballbat->draw();
	}
	else {
		rigidScene->draw();
	}
	prevMode = mode;
	// draw the floor
	
}
