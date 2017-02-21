#ifndef TANK
#define TANK

#include "globals.h"
#include "polygon3d.h"
#include <math.h>
#include <vector>
#include "projectile.h"
class Projectile;

class Tank{

public:
	Point center;
	Point hitSphereCenter;
	double hitSphereRadius;
	double baseAngle, towerAngle, cannonAngle, scale;
	bool laser;
	double tankSpeed;
	int cooldown;
	int health;	

	std::vector<Polygon3d> base, tower, cannon;
	std::vector< std::vector<Polygon3d> > totalBoundingBox; //contains bounding box of all tank components
	Tank(Point center);
	void drawHealthBar(int health);
	void draw();
	void shoot();
	void update(double tankSpeed, double tankBaseRotate, double tankTurretRotate, double tankCannonRotate, int cameraMode); // make the pendulum keep up with the frame rate
	bool onLock(int x, int y);
	void turretFollowMouse(int x, int y, int cameraMode);//turret + cannon follow mouse cursor
	std::vector<std::vector<Polygon3d> > boundingBox(void);//return vector of vectors of individual bounding boxes
};

#endif
