#ifndef TANK
#define TANK

#include "globals.h"
#include "polygon3d.h"
#include <math.h>
#include <vector>

class Tank{
public:
	Point center;
	double baseAngle, towerAngle, cannonAngle, scale;
	bool laser;

	std::vector<Polygon3d> base, tower, cannon;
	Tank(Point center);
	void draw();
	void shoot();
	void update(); // make the pendulum keep up with the frame rate
	std::vector<Polygon3d> boundingBox();
};

#endif
