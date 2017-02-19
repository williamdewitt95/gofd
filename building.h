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

	static const double sidewalkWidth;
	static const double sidewalkThickness;
	static const double maxBuildingWidth;
	static const double distanceBetweenBuildings;
	static const double streetWidth; // distanceBetweenBuildings - maxBuildingWidth;

	Building(Point center);
	void draw();
	void update();
	std::vector<Polygon3d> boundingBox();
};

#endif
