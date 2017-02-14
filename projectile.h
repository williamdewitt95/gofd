#ifndef PROJECTILE
#define PROJECTILE

#include "globals.h"
#include "polygon3d.h"
#include <math.h>
#include <vector>

class Projectile{
public:
	Point center;

	std::vector<Polygon3d> boundingBox;
	Projectile(Point center);
	void draw();
	void update();
	std::vector<Polygon3d> getBoundingBox();
};

#endif