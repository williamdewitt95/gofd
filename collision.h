#ifndef COLLISION
#define COLLISION

#include <GL/glut.h>
#include <GL/glu.h>
#include <vector>
#include <math.h>
#include "vector_basics.h"
#include "polygon3d.h"
#include "tank.h"
#include "building.h"
#include "globals.h"
#include "target.h"

double distance(Point a, Point b);
double distance(Vector a, Vector b);
bool sphereToPlane(Point c, double radius,Vector n, Point p);
void collisionDetect(Tank* tank, std::vector<Building*>& buildings, std::vector<Target*>& targets, std::vector<Projectile*>& projectiles);



#endif
