#ifndef GLOP_BUILDING
#define GLOP_BUILDING

#include "globals.h"
#include "polygon3d.h"
#include <math.h>
#include <vector>
#include <time.h>

class Building{
public:
	Point center;

	std::vector<Polygon3d> model;
	std::vector<Polygon3d> box;

	static const double distanceBetweenBuildings = 60;
	Building(Point center);
	void draw();
	void update(); // make the pendulum keep up with the frame rate
	std::vector<Polygon3d> boundingBox();
};

#endif
