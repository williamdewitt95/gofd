#ifndef TANK
#define TANK

#include "globals.h"
#include <math.h>
#include <vector>
#include <sstream>
#include "projectile.h"

class Tank:public DrawableObject{

public:
	Point hitSphereCenter;
	double hitSphereRadius;
	double baseAngle, towerAngle, cannonAngle, scale;
	bool laser, tankRecoil;
	double tankSpeedX, tankSpeedY, tankSpeed, recoilSpeed, recoilAngle, towerToBaseAngle;
	double rollingFriction, kineticFriction;
	int cooldown;
	int health;

	std::vector<Polygon3d> base, tower, cannon;
	std::vector<Polygon3d> baseBoundingBox, towerBoundingBox, cannonBoundingBox;

	Tank(Point center);
	void drawHealthBar();
	void drawCooldownBar();
//	void drawScore();
	void draw();
	void shoot();
	void applyRecoil();
	void update(double tankBaseRotate, double tankTurretRotate, double tankCannonRotate, int cameraMode, double tankAccel); // make the pendulum keep up with the frame rate
	bool onLock(int x, int y);
	void turretFollowMouse(int x, int y, int cameraMode);//turret + cannon follow mouse cursor
	std::vector<Polygon3d> boundingBox(void);//return vector of vectors of individual bounding boxes
};

#endif
