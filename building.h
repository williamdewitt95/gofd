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

	static constexpr double sidewalkWidth = 3;
	static constexpr double maxBuildingWidth = 40;
	static constexpr double distanceBetweenBuildings = 60;
	static constexpr double streetWidth = distanceBetweenBuildings - maxBuildingWidth;
	Building(Point center);
	void draw();
	void update();
	std::vector<Polygon3d> boundingBox();
};

#endif
