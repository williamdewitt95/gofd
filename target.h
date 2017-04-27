#ifndef TARGET
#define TARGET

#include "globals.h"
#include "polygon3d.h"
#include <math.h>
#include <vector>
#include "drawableObject.h"

class Target:public DrawableObject{
private:
	double rotation;
	GLuint mascotChoice;
public:
	double radius;

	Target(Point center);
	void draw();
	void update();
	
	void setRotation(double);
};

#endif


