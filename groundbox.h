#ifndef GROUNDBOX
#define GROUNDBOX

#include "globals.h"
#include "polygon3d.h"
#include <math.h>
#include <vector>
#include "drawableObject.h"

class Groundbox: public DrawableObject
{
private:

public:
	Groundbox(double buildingWidth, double streetWidth);
	void draw();
}


#endif