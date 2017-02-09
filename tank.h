#ifndef TANK
#define TANK

#include "globals.h"
#include "polygon3d.h"
#include <math.h>
#include <vector>

class Tank{
public:
	Point center;
	std::vector<Polygon3d> sides;
	std::vector<Polygon3d> boundingBox;

	Tank(Point center);
	void draw();
	void update(); 
	std::vector<Polygon3d> getBoundingBox();
};

#endif
