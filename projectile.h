#ifndef PROJECTILE
#define PROJECTILE

#include "globals.h"
#include "polygon3d.h"
#include "drawableObject.h"

#include <math.h>
#include <vector>

struct Explosion{
	double x;
	double y;
	double z;
	int decay;
	int staticDecay;
	double expansionRate;
	double radius;
};

class Projectile:public DrawableObject{
private:
	double drag(double speed);
	double f(double p, double q, double drag);
	double g(double p, double q, double drag);
	void step();
	std::vector<Explosion> explosions;

	void baseInit(Point center, Point tankStart, double angleV, double angleH); // sets variable to the known most basic values
public:
	enum{MOVING,EXPLODING,DEAD};
	int state; // is one of the above
	Point oldCenter;

	Point tankStart, local;
	double angleV, angleH, velocity, mass, C;
	double h, t, x, y, p, q;

	//std::vector<Polygon3d> boundingBox;
	//std::vector<Polygon3d> model;
	Projectile(Point center);
	Projectile(Point center, Point tankStart, double angleV, double angleH); //Vertical Angle = angleV, horizontal angle = angleH
	void draw();
	void update();
	void drawExplosion(struct Explosion *ex);
	void setExploding();
	void setExploding(Point p);
};

#endif