// modelerview.h

// This is the base class for all your models.  It contains
// a camera control for your use.  The draw() function will 
// set up default lighting and apply the projection, so if you 
// inherit, you will probably want to call ModelerView::draw()
// to set up the camera.

#ifndef MODELERVIEW_H
#define MODELERVIEW_H
#include <chrono>
using namespace std::chrono;
#include <FL/Fl_Gl_Window.H>
//#include "modelerui.h"
class Camera;
class ModelerView;
//class ModelerUI;
typedef ModelerView* (*ModelerViewCreator_f)(int x, int y, int w, int h, char *label);

typedef enum { CTRL_MODE, CURVE_MODE } cam_mode_t;

class ModelerView : public Fl_Gl_Window
{
public:
	//ModelerUI * mui;
	bool simulate;
    ModelerView(int x, int y, int w, int h, char *label=0);
	static void callback1(void*);
	virtual ~ModelerView();
    virtual int handle(int event);
    virtual void draw();
	bool jump;
	bool leanf;
	bool leanb;
	void setBMP(const char *fname);
	void saveBMP(const char* szFileName);
	void endDraw();

	void camera(cam_mode_t mode);
    Camera *m_camera;
	Camera *m_ctrl_camera;
	Camera *m_curve_camera;
	milliseconds prevTime;
	static int keyhandler(int event);

	double prevy;
	
	
	float t;
	void update();
	bool save_bmp;
};


#endif
