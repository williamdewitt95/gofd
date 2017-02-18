#ifndef TARGET
#define TARGET

#include "globals.h"
#include "polygon3d.h"
#include <math.h>
#include <vector>

class Target{
private:
	double rotation;

public:
	Point center;
	std::vector<Polygon3d> boundingBox;
	double radius;

	unsigned int listName;

	Target(Point center);
	void draw();
	void draw_CPU();
	void update(); 
	std::vector<Polygon3d> getBoundingBox();
};

#endif


