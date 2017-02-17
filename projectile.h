#ifndef PROJECTILE
#define PROJECTILE

#include "globals.h"
#include "polygon3d.h"
#include <math.h>
#include <vector>

class Projectile{
public:
	Point center, tankStart, local;
	double angleV, angleH, velocity, mass, drag;
	double step, t, x, y, p, q;

	std::vector<Polygon3d> boundingBox;
	Projectile(Point center);
	Projectile(Point center, Point tankStart, double angleV, double angleH); //Vertical Angle = angleV, horizontal angle = angleH
	void draw();
	void update();
	std::vector<Polygon3d> getBoundingBox();
};

#endif