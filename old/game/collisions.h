#ifndef COLLISIONS
#define COLLISIONS

#include "globals.h"

int intersect3D_SegmentPlane( LineSeg seg, Polygon3d poly, Point &I );
void collisionTest();

#endif