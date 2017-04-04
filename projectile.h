#ifndef PROJECTILE
#define PROJECTILE

#include "globals.h"

#include "polygon3d.h"

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

struct Trail{
	double x;
	double y;
	double z;
	int decay;
	int staticDecay;
};
//extern std::vector<Explosion> explosions;

class Projectile{
private:
	int trailInterval;
	double drag(double speed);
	double f(double p, double q, double drag);
	double g(double p, double q, double drag);
	void step();
	std::vector<Explosion> explosions;
	std::vector<Trail> trails;
public:
	Point center, tankStart, local;
	double angleV, angleH, velocity, mass, C;
	double h, t, x, y, p, q;
	bool hasExploded;

	std::vector<Polygon3d> boundingBox;
	Projectile(Point center);
	Projectile(Point center, Point tankStart, double angleV, double angleH); //Vertical Angle = angleV, horizontal angle = angleH
	void draw();
	void update();
	void explode(struct Explosion *ex);
	void drawTrails(std::vector<Trail>& trailList);
	std::vector<Polygon3d> getBoundingBox();
};

#endif