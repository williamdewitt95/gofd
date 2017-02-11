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
	void update(double tankSpeed, double tankBaseRotate, double tankTurretRotate, double tankCannonRotate); // make the pendulum keep up with the frame rate
	void turretFollowMouse(int x, int y);
	std::vector<Polygon3d> boundingBox();
};

#endif
