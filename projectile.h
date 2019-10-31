#ifndef PROJECTILE
#define PROJECTILE

#include "globals.h"
#include "polygon3d.h"
#include "drawableObject.h"

#include <math.h>
#include <vector>
#include <chrono>

struct Explosion{
	double x;
	double y;
	double z;
	int decay;
	int staticDecay;
	double expansionRate;
	double radius;
};

struct Trail{
	double x;
	double y;
	double z;
	int decay;
	int staticDecay;
};

class Projectile:public DrawableObject{
private:
	int trailInterval;
	double drag(double speed);
	double f(double p, double q, double drag);
	double g(double p, double q, double drag);
	void step();
	std::vector<Explosion> explosions;
	std::vector<Trail> trails;
	float projR, projG, projB;

	void baseInit(Point center, Point tankStart, double angleV, double angleH); // sets variable to the known most basic values
public:
	enum{MOVING,EXPLODING,DYING,DEAD};
	int state; // is one of the above
	Point oldCenter;
	int invincibility;

	Point tankStart, local;
	double angleV, angleH, velocity, mass, C;
	double h, x, y, p, q;
	std::chrono::steady_clock::time_point simTime; // current time in the simulted projectile path

	//std::vector<Polygon3d> boundingBox;
	//std::vector<Polygon3d> model;
	Projectile(Point center);
	Projectile(Point center, Point tankStart, double angleV, double angleH); //Vertical Angle = angleV, horizontal angle = angleH
	Projectile(Point center, Point tankStart, double angleV, double angleH, float tankR, float tankG, float tankB);
	void draw();
	void update();
	void drawExplosion(struct Explosion *ex);
	void setExploding();
	void setExploding(Point p);
	void drawTrails(std::vector<Trail>& trailList);
};

#endif