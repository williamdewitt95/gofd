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
	double tankSpeed;

	std::vector<Polygon3d> base, tower, cannon;
	std::vector< std::vector<Polygon3d> > totalBoundingBox; //contains bounding box of all tank components
	Tank(Point center);
	void draw();
	void shoot();
	void update(double tankSpeed, double tankBaseRotate, double tankTurretRotate, double tankCannonRotate, int cameraMode); // make the pendulum keep up with the frame rate
	void turretFollowMouse(int x, int y, int cameraMode);//turret + cannon follow mouse cursor
	std::vector<std::vector<Polygon3d> > boundingBox(void);//return vector of vectors of individual bounding boxes
};

#endif
