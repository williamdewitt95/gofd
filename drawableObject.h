#ifndef DRAWABLE_OBJECT
#define DRAWABLE_OBJECT

#include <vector>
#include "polygon3d.h"

class DrawableObject{
protected:
	std::vector<Polygon3d> boundingBox;
	std::vector<Polygon3d> model;
public:
	virtual void draw();
	virtual void update();
	virtual std::vector<Polygon3d> getBoundingBox();

	virtual bool collidesWith(const DrawableObject&); //do these two objects collide
	virtual bool collidesWith(const Vector); //does this vector pass through our model

	// add some collision point here for an entire object also
	virtual bool collisionPoint(const Vector); //for a given line, where on that line does it collide
	                                            //this returns the point from the the first end of the vector to the second
};

#endif