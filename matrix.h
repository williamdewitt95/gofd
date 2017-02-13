#ifndef MATRIX
#define MATRIX

#include <math.h>
#include <stdio.h>
#include <vector>
#include "vector_basics.h"
#include "polygon3d.h"

//class matrix;

class matrix{
protected:
	//ele is for matrix ELEments in order to shorten it
	double ele[4*4]; //since the operations in this program are always in 3d
		         //we only allow for 3d transformation matrices

public:
	matrix();
	matrix(std::vector<Vector>& columns);
	matrix(double elements[]);
	matrix(Polygon3d object);

	Vector& matTransform(Vector test);//Transforms a vector based on what the matrix objects elements array is set to
	Vector matSet(Polygon3d object);//This should create a transformation matrix based on the passed in polygon3d object

};
#endif
