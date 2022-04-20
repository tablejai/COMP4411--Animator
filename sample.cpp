// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include "Spider.h"
#include <FL/gl.h>
#include "SpiderModel.h"
#include "modelerglobals.h"

// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView
{
public:
	SampleModel(int x, int y, int w, int h, char* label)
		: ModelerView(x, y, w, h, label) { }

	virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char* label)
{
	return new SampleModel(x, y, w, h, label);
}
Spider* spider;
ModelerView* createSpiderModel(int x, int y, int w, int h, char* label)
{

	return new SpiderModel(x, y, w, h, label);
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void SampleModel::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	ModelerView::draw();

	// draw the floor
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(-5, 0, -5);
	drawBox(0.01f, 0.01f, 0.01f);
	glPopMatrix();

	// draw the sample model
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_GREEN);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

	glPushMatrix();
	glTranslated(-1.5, 0, -2);
	glScaled(3, 1, 4);
	drawBox(2, 2, 2);
	glPopMatrix();

	// draw cannon
	glPushMatrix();
	glRotated(VAL(ROTATE), 0.0, 1.0, 0.0);
	glRotated(-90, 1.0, 0.0, 0.0);
	drawCylinder(VAL(HEIGHT), 0.1, 0.1);

	glTranslated(0.0, 0.0, VAL(HEIGHT));
	drawCylinder(1, 1.0, 0.9);

	glTranslated(0.0, 0.0, 0.5);
	glRotated(90, 1.0, 0.0, 0.0);
	drawCylinder(4, 0.1, 0.2);
	glPopMatrix();

	glPopMatrix();
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
	ModelerControl controls[NUMCONTROLS];
	controls[XPOS] = ModelerControl("X Position", -5, 5, 0.01f, 0);
	controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.01f, 0);
	controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.01f, 0);
	controls[XTHETA] = ModelerControl("X Theta", 0, 360, 0.01f, 0);
	controls[YTHETA] = ModelerControl("Y Theta", 0, 360, 0.01f, 0);
	controls[ZTHETA] = ModelerControl("Z Theta", 0, 360, 0.01f, 0);
	controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.01f, 1);
	controls[OSCILLATEY] = ModelerControl("Walk", 0, 200, 0.01f, 0);
	controls[RESOLUTIONMETABALL] = ModelerControl("RESOLUTIONMETABALL", 0.13, 1, 2.0f, 1);
	controls[LSYSTEMDISPLAY] = ModelerControl("L-System Display", 0, 1, 0.0, 0);
	controls[LSYSTEMOBJECTTYPE] = ModelerControl("L-System ObjectType", 0, 3, 0, 0);
	controls[LSYSTEMDVALUE] = ModelerControl("L-System d-value", 0, 1, 2.0f, 1);
	controls[LSYSTEMINITIALANGLE] = ModelerControl("L-System Initial Angle", 0, 360, 0.01f, 0);
	controls[LSYSTEMITER] = ModelerControl("L-System iteration", 0, 10, 1.0f, 1);
	controls[MOVECANON] = ModelerControl("MOVECANON", 0, 180, 0.01f, 1);
	controls[CHANGE_LEG] = ModelerControl("Leg selections", 0, 1, 0, 0);
	controls[CHANGE_BODY] = ModelerControl("Body selections", 0, 1, 0, 0);
	controls[CHANGE_HEAD] = ModelerControl("Head selections", 0, 1, 0, 0);
	controls[FRAME] = ModelerControl("Frame Enabled", 0, 1, 0, 0);
	controls[ANIMATE] = ModelerControl("Animate", 0, 1, 0.01f, 0);
	controls[HIGHNESS] = ModelerControl("Highness", 0, 1, 1.0f, 0);
	controls[ROTATE] = ModelerControl("Rotate", -135, 135, 0.01f, 0);
	controls[TENTACLE_X_TAR] = ModelerControl("Tentacle X Position", -2.5, 2.5, 1.0f, 3.3);
	controls[TENTACLE_Y_TAR] = ModelerControl("Tentacle Y Position", -5.0, 5, 1.0f, 0);
	controls[TENTACLE_Z_TAR] = ModelerControl("Tentacle Z Position", -5.0, 5, 1.0f, 0);
	controls[TENTACLE_ANG_CONSTRAINT] = ModelerControl("Tentacle Angle Constraint", -135, 135, 1.0f, 0);
	controls[LEVEL_OF_DETAIL] = ModelerControl("Level of Detail", 0, 5, 0.01f, 5);
	


	// ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
	 //ModelerApplication::Instance()->Init(&(createSpiderModel), controls, NUMCONTROLS);
	ModelerApplication::Instance()->Init(&(createSpiderModel), controls, NUMCONTROLS);


	return ModelerApplication::Instance()->Run();
}
