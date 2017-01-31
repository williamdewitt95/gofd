#ifndef GLOP_BUILDING
#define GLOP_BUILDING

#include "globals.h"
#include "polygon3d.h"
#include <math.h>
#include <vector>

class Building{
public:
	Point center;

	std::vector<Polygon3d> sides;
	Building(Point center);
	void draw();
	void update(); // make the pendulum keep up with the frame rate
	std::vector<Polygon3d> boundingBox();
};

#endif