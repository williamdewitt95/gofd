#ifndef glop102_polygon3d
#define glop102_polygon3d

#include <stdio.h>
#include <vector>
#include <GL/glut.h>
#include "vector_basics.h"

//===================================================================
// POLYGON CLASS
//===================================================================
// This does all the basics that a drawn polygon should care about
// NOTE!!!
// When specifying points, the first and last point must be the same
// We are wanting to make sure that when you draw lines the polygon is closed
// MAKE SURE THE FIRST AND LAST POINT ARE THE SAME
//===================================================================
// This draws polygons using the draw function in a realative manner
// so if GL has the matrix moved for the world before calling the draw
// function, then polygon will be drawn relative to the moved location
//===================================================================

class Polygon3d{
protected: // we let our children get to this but not the world
	Point center;
	Vector rotation;
	double scale;

	Vector velocity;
	Vector rotationSpeed;

	std::vector<Point> vertexList;

	bool drawTesselate;
	GLubyte color[4]; //RGBA - 1 byte a piece

	double maxRadius; // special little optimization for collision checking

	GLuint texture;
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
	void setScale(double);
	double getScale();
	void setCenter(Point);
	Point getCenter();
	void setColor(GLubyte red,GLubyte green, GLubyte blue);
	void setColor(GLubyte red,GLubyte green, GLubyte blue, GLubyte alpha);
	GLubyte getColor(int channel);
	void setTesselation(bool tes);
	bool getTesselation();
	void setVelocity(double x, double y, double z);
	void setVelocity(Vector& x);
	Vector getVelocity();
	void setRotationSpeed(Vector&);
	Vector getRotationSpeed();
	double getMaxRadius();
	bool intersection(Polygon3d other);
	bool intersectsLineSeg(LineSeg ls);

	Vector normal;

	bool planesIntersection(Polygon3d other);

	void setTexture(GLuint tex);
	GLuint getTexture();
	std::vector<Point>& getTexturePoints();
	Point& getTexturePos(int index);
	bool hasTexture();
	void removeTexture();

	int numPoints()const;
	std::vector<Point>& getPoints(); // get the list of points for you to affect the shape with
	Point& operator[](int); // get point number x back
	Polygon3d& operator=(Polygon3d);

	Polygon3d getTransform(); // get the transform of the points of the polygon to where they should be
	void recenter(); // moves the center of the polygon to be at the centroid of the shape but does not change its position

	Polygon3d getWorldPoints();

	void draw();
	static void __secretVertexDrawingFunction(void *data, void *polygon);
	void update();
};

#endif
