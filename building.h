#ifndef GLOP_BUILDING
#define GLOP_BUILDING

#include "globals.h"
#include <math.h>
#include <vector>

class Building : public DrawableObject{
public:
	//std::vector<Polygon3d> model;
	//std::vector<Polygon3d> collisionBox;

	static const double sidewalkWidth;
	static const double sidewalkThickness;
	static const double maxBuildingWidth;
	static const double distanceBetweenBuildings;
	static const double streetWidth; // distanceBetweenBuildings - maxBuildingWidth;

	unsigned int listName; // used for on GPU rendering
	std::vector<unsigned int> subLists;
	std::vector<unsigned int> sideSouth,sideEast, sideNorth, sideWest; // special decerations that are only visable on these sides

	Building(Point center);
	void draw();
	void draw_CPU();
};

#endif
