#ifndef glop102_polygon3d
#define glop102_polygon3d

#include <string>
#include <stdio.h>
#include <vector>
#include <GL/glu.h>
#include "vector_basics.h"

//===================================================================
// POLYGON CLASS
//===================================================================
// This is a general class that is meant for CPU bound tasks.
// Some other objects will allow you to pass in polygon objects
// but if it is meant to be drawn, the polygon will be transformed
// into a form more usable for the GPU.
//===================================================================

class Polygon3d{
protected: // we let our children get to this but not the world
	Point center;
	Vector rotation;
	double scale;
	GLubyte color[4]; //RGBA - 1 byte a piece
	Vector normal;

	std::vector<Point> vertexList;

	double maxRadius; // special little optimization for collision checking

	std::string texture;
	bool hasTex;
	std::vector<Point> vertexTextureList;
public:
	Polygon3d();
	Polygon3d(double,double,double); // specifies the center
	Polygon3d(std::vector<Point>&);
	Polygon3d(Point pnt, std::vector<Point>& points);
	Polygon3d(Triangle &);
	Polygon3d(const Polygon3d&);

	void setRotation(Vector&);
	Vector getRotation();
	void setScale(double&);
	double getScale();
	void setCenter(Point&);
	Point getCenter();
	void setColor(GLubyte& red,GLubyte& green, GLubyte& blue);
	void setColor(GLubyte& red,GLubyte& green, GLubyte& blue, GLubyte& alpha);
	GLubyte getColor(int& channel);
	double getMaxRadius();
	void setNormal(Vector&);
	void calculateNormal();
	Vector getNormal();

	void setTexture(std::string&);
	std::string getTexture();
	std::vector<Point>& getTexturePoints();
	Point& getTexturePos(int index);
	bool hasTexture();
	void removeTexture();

	int numPoints()const;
	std::vector<Point>& getPoints(); // get the list of points for you to affect the shape with
	Point& operator[](int); // get point number x back
	Polygon3d& operator=(Polygon3d);

	Polygon3d getTransform(); // get the transform of the points of the polygon to where they should be
};

#endif
