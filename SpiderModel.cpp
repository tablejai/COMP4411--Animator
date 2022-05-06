#include "SpiderModel.h"
SpiderModel:: SpiderModel(int x, int y, int w, int h, char* label): ModelerView(x, y, w, h, label) {
	
	spider = new Spider(0, 0,0, 4, 2, 2, this);
	ballbat =   new BallBat(0, 0, 0, 4, 2, 2, this);
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
	else
	{
		if (prevMode != mode)
			ballbat->setup();
		ballbat->draw();
	}
	prevMode = mode;
	// draw the floor
	
}
