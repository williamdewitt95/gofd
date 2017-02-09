#include "target.h"

Target::Target(Point center)
{
    this->center = center;
}

void Target::draw()
{
    glColor3f(0.0, 0.0, 1.0);
    GLUquadricObj *cylinder;
    glPushMatrix();
    glRotated(90, 1, 0, 0);
	glTranslated(center.x,center.y,center.z);
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, .6, .6, .1, 30, 1);
	glPopMatrix();
}

void Target::update()
{

}

std::vector<Polygon3d> Target::getBoundingBox()
{
    return this->boundingBox;

}
