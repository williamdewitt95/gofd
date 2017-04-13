#ifndef TARGET
#define TARGET

#include "globals.h"
#include "polygon3d.h"
#include <math.h>
#include <vector>

class Target{
private:
	double rotation;
	double rVal, gVal, bVal;
public:
	Point center;
	std::vector<Polygon3d> boundingBox;
	double radius;

	Target(Point center);
	void draw();
	void update(); 
	std::vector<Polygon3d> getBoundingBox();
	
	void setRotation(double);
};

#endif


