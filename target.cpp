#include "target.h"

Target::Target(Point center)
{
    this->center = center;
    this->radius = 3;
    this->rotation = 0;
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

    // optimize it for further runtime
    listName = glGenLists(1);
    glNewList(listName,GL_COMPILE);
    this->draw_CPU();
    glEndList();
}

void Target::draw(){
    glPushMatrix();

    glTranslated(center.x,center.y,center.z);
    glRotated(90, 1, 0, 0);
    glRotated(this->rotation, 0, 1, 0);
    glCallList(listName);

    glPopMatrix();
}
void Target::draw_CPU()
{
    // glPushMatrix();

    glColor3f(0.0, 0.0, 1.0);
    GLUquadricObj *cylinder = gluNewQuadric();
    GLUquadricObj *topDisk = gluNewQuadric();
    GLUquadricObj *bottomDisk = gluNewQuadric();
    gluQuadricDrawStyle(cylinder, GLU_FILL);

    glPushMatrix();
    	glTranslated(center.x,center.y,center.z);
        glRotated(90, 1, 0, 0);
        glRotated(this->rotation, 0, 1, 0);

    	gluCylinder(cylinder, this->radius, this->radius, .1, 30, 1);

        gluDisk(topDisk, 0, this->radius, 30, 1);

        gluDisk(bottomDisk, this->radius, 4, 30, 1);
	glPopMatrix();
}

void Target::update(){
}

std::vector<Polygon3d> Target::getBoundingBox()
{
    return this->boundingBox;

}
void Target::setRotation(double rot)
{
	this->rotation = rot;
}
