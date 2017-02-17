#include "projectile.h"

Projectile::Projectile(Point center){
	this->center = center;
	this->angleV = 45;
	this->angleH = 0;

	{
		boundingBox.push_back(Polygon3d());
		auto &points = boundingBox[boundingBox.size()-1].getPoints();

		points.push_back(Point(  -5, -5,  20));
		points.push_back(Point(  -5, -5,   0));
		points.push_back(Point(   5, -5,   0));
		points.push_back(Point(   5, -5,  20));
		points.push_back(Point(  -5, -5,  20));
	}
	{
		boundingBox.push_back(Polygon3d());
		auto &points = 	boundingBox[boundingBox.size()-1].getPoints();

		points.push_back(Point(   5,  5,  20));
		points.push_back(Point(   5,  5,   0));
		points.push_back(Point(  -5,  5,   0));
		points.push_back(Point(  -5,  5,  20));
		points.push_back(Point(   5,  5,  20));
	}
	{
		boundingBox.push_back(Polygon3d());
		auto &points = boundingBox[boundingBox.size()-1].getPoints();

		points.push_back(Point(   5, -5,  20));
		points.push_back(Point(   5, -5,   0));
		points.push_back(Point(   5,  5,   0));
		points.push_back(Point(   5,  5,  20));
		points.push_back(Point(   5, -5,  20));
	}
	{
		boundingBox.push_back(Polygon3d());
		auto &points = boundingBox[boundingBox.size()-1].getPoints();

		points.push_back(Point(  -5,  5,  20));
		points.push_back(Point(  -5,  5,   0));
		points.push_back(Point(  -5, -5,   0));
		points.push_back(Point(  -5, -5,  20));
		points.push_back(Point(  -5,  5,  20));
	}

	{
		boundingBox.push_back(Polygon3d());
		auto &points = boundingBox[boundingBox.size()-1].getPoints();

		points.push_back(Point(  -5,  5,  20));
		points.push_back(Point(  -5,  5,   0));
		points.push_back(Point(  -5, -5,   0));
		points.push_back(Point(  -5, -5,  20));
		points.push_back(Point(  -5,  5,  20));
	}
}

Projectile::Projectile(Point center, double angleV, double angleH)
{
	this->center = center;
	this->angleV = angleV;
	this->angleH = angleH;
}

void Projectile::draw(){
	glPushMatrix();

	GLUquadricObj *shellCasing, *shellPoint, *shellBottom;
	glColor3f(.1, .1, .1);
	glTranslated(center.x,center.y,center.z);
	glTranslated(.2, 0, 0);
	glRotated(90.0, 0.0, 1.0, 0.0);
	shellCasing = gluNewQuadric();
	gluCylinder(shellCasing, .05, .05, .2, 30, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.1, .1, .1);
	glTranslated(center.x,center.y,center.z);
	glTranslated(.4, 0, 0);
	glRotated(90.0, 0.0, 1.0, 0.0);
	shellBottom = gluNewQuadric();
	gluDisk(shellBottom, 0, .05, 30, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(center.x,center.y,center.z);
	glTranslated(-.2, 0, 0);
	glRotated(90.0, 0.0, 1.0, 0.0);
	shellPoint = gluNewQuadric();
	gluCylinder(shellPoint, 0, .05, .4, 30, 4);
	glPopMatrix();
}

void Projectile::update()
{
}

std::vector<Polygon3d> Projectile::getBoundingBox(){
	return this->boundingBox;
}
