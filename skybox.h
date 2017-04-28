#ifndef SKYBOX
#define SKYBOX

#include "globals.h"
#include "polygon3d.h"
#include <math.h>
#include <vector>
#include "drawableObject.h"

class Skybox:public DrawableObject
{
private:

public:
	Skybox();
	void draw();
	void update();
};

#endif