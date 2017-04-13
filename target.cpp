#include "target.h"

Target::Target(Point center)
{
    this->center = center;
    this->radius = 3;
    this->rotation = 0;
    this->rVal = 0.0;
    this->gVal = 0.0;
    this->bVal = 1.0;
    {
        boundingBox.push_back(Polygon3d());
        auto &points = boundingBox[boundingBox.size()-1].getPoints();
        points.push_back(Point(-3, -3, 0));
        points.push_back(Point(3, -3, 0));
        points.push_back(Point(3, 3, 0));
        points.push_back(Point(-3, 3, 0));
        points.push_back(Point(-3, -3, 0));
    }

    {
        boundingBox.push_back(Polygon3d());
        auto &points = boundingBox[boundingBox.size()-1].getPoints();
        points.push_back(Point(  3, -3,  0));
        points.push_back(Point(  3, -3, .1));
        points.push_back(Point(  3,  3, .1));
        points.push_back(Point(  3,  3,  0));
        points.push_back(Point(  3, -3,  0));
    }

    {
        boundingBox.push_back(Polygon3d());
        auto &points = boundingBox[boundingBox.size()-1].getPoints();
        points.push_back(Point( -3,  3,  0));
        points.push_back(Point( -3,  3, .1));
        points.push_back(Point(  3,  3, .1));
        points.push_back(Point(  3,  3,  0));
        points.push_back(Point( -3,  3,  0));
    }

    {
        boundingBox.push_back(Polygon3d());
        auto &points = boundingBox[boundingBox.size()-1].getPoints();
        points.push_back(Point( -3, -3,  0));
        points.push_back(Point( -3, -3, .1));
        points.push_back(Point(  3, -3, .1));
        points.push_back(Point(  3, -3,  0));
        points.push_back(Point( -3, -3,  0));
    }

    {
        boundingBox.push_back(Polygon3d());
        auto &points = boundingBox[boundingBox.size()-1].getPoints();
        points.push_back(Point( -3, -3,  0));
        points.push_back(Point( -3, -3, .1));
        points.push_back(Point( -3,  3, .1));
        points.push_back(Point( -3,  3,  0));
        points.push_back(Point( -3, -3,  0));
    }

    {
        boundingBox.push_back(Polygon3d());
        auto &points = boundingBox[boundingBox.size()-1].getPoints();
        points.push_back(Point( -3, -3, .1));
        points.push_back(Point(  3, -3, .1));
        points.push_back(Point(  3,  3, .1));
        points.push_back(Point( -3,  3, .1));
        points.push_back(Point( -3, -3, .1));
    }
}

void Target::draw()
{
    glColor3f(rVal, gVal, bVal);
    GLUquadricObj *cylinder;
    GLUquadricObj *topDisk, *bottomDisk;
    glPushMatrix();
	glTranslated(center.x,center.y,center.z);
    glRotated(90, 1, 0, 0);
    glRotated(this->rotation, 0, 1, 0);
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, this->radius, this->radius, .1, 30, 1);
    topDisk = gluNewQuadric();
    gluDisk(topDisk, 0, this->radius, 30, 1);
    bottomDisk = gluNewQuadric();
    gluDisk(bottomDisk, this->radius, 4, 30, 1);
	glPopMatrix();
}

void Target::update()
{
//    this->rotation += 1;
    this->rVal = ((float) rand()) / (RAND_MAX);
    this->gVal = ((float) rand()) / (RAND_MAX);
    this->bVal = ((float) rand()) / (RAND_MAX); 	
    this->draw();
}

std::vector<Polygon3d> Target::getBoundingBox()
{
    return this->boundingBox;

}
void Target::setRotation(double rot)
{
	this->rotation = rot;
}
