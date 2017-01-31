#ifndef VECTOR_BASICS
#define VECTOR_BASICS

#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979

class Point;
class Vector;
class LineSeg;

class Point{
public:
	union{ // make it so we can access the data as array or xyz
		struct{
			double x,y,z;
		};
		double data[3];
	};
	Point();
	Point(double x, double y, double z);

	//==============================================================================
	//  OPERATOR OVERLOADS
	//==============================================================================
	Point& operator+=(const Vector& other);
	Point& operator+=(const Point& other);
	Point operator+(const Vector& other);
	Point operator+(const Point& other);
	Point& operator*=(const double scale);
	Point operator*(const double scale);
	Point& operator/=(const double scale);
	Point operator/(const double scale);
	bool operator==(const Point& other);
	bool operator!=(const Point& other);
	double& operator[](const int index);
};

class Vector{
public:
	union{ // make it so we can access the data as array or xyz
		struct{
			double x,y,z;
		};
		double data[3];
	};
	Vector();
	Vector(double x, double y, double z);
	Vector(Point& p1, Point& p2);

	//==============================================================================
	//  BASIC VECTOR OPERATIONS
	//==============================================================================
	double magnitude();
	double length();
	double dot(Vector& other);
	double dotProduct(Vector& other);
	Vector cross(const Vector& other);
	Vector crossProduct(Vector& other);

	//==============================================================================
	//  OPERATOR OVERLOADS
	//==============================================================================
	Vector& operator+=(const Vector& other);
	Vector operator+(const Vector& other);
	Vector& operator-=(const Vector& other);
	Vector operator-(const Vector& other);
	Vector& operator*=(const double scale);
	Vector operator*(const double scale);
	Vector& operator/=(const double scale);
	Vector operator/(const double scale);
	bool operator==(const Vector& other);
	bool operator!=(const Vector& other);
	double& operator[](const int index);
};

class LineSeg{
public:
	Point p1;
	Point p2;
	LineSeg();
	LineSeg(const Point& p1, const Point& p2);
	LineSeg(Point p1, const Vector& v);

	bool intersect(LineSeg& other);
	Point intersection(LineSeg& other);
	Point& operator[](const int& index);
	Vector direction();
};

struct Triangle{
	Point p1,p2,p3;
};

#endif