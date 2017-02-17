#ifndef PROJECTILE
#define PROJECTILE

#include "globals.h"
#include "polygon3d.h"
#include <math.h>
#include <vector>

class Projectile{
public:
	Point center;
	dobule angleV, angleH;

	std::vector<Polygon3d> boundingBox;
	Projectile(Point center);
	Projectile(point center, double angleV, double angleH); //Vertical Angle = angleV, horizontal angle = angleH
	void draw();
	void update();
	std::vector<Polygon3d> getBoundingBox();
};

#endif