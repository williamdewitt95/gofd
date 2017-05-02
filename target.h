#ifndef TARGET
#define TARGET

#include "globals.h"
#include "polygon3d.h"
#include <math.h>
#include <vector>
#include "drawableObject.h"

class Target:public DrawableObject{
protected:
	double rotation;
	GLuint mascotChoice;
public:
	enum{NORMAL,DEAD};
	double radius;
	int state;

	Target(Point center);
	void draw();
	void draw_map_marker();
	void update();
	
	//to set degree a single target will be rotated; used when placing on buildings
	void setRotation(double);
};

#endif


