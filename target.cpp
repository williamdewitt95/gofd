#include "target.h"
#include "globals.h"
#include <stdlib.h>

Target::Target(Point center)
{
    this->center = center;
    this->radius = 3;
    this->rotation = 0;
    this->mascotChoice = rand() % 5;
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

void Target::draw(){
    glPushMatrix();

    // glTranslated(center.x,center.y,center.z);
    // glRotated(90, 1, 0, 0);
    // glRotated(this->rotation, 0, 1, 0);

    GLUquadricObj *cylinder = gluNewQuadric();
    GLUquadricObj *topDisk = gluNewQuadric();
    GLUquadricObj *bottomDisk = gluNewQuadric();
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    loadTex("textures/buildings/brick1.png");
    glBindTexture(GL_TEXTURE_2D,GLOBAL.TEXTURES_LOADED["textures/buildings/brick1.png"].textureRef);

    glPushMatrix();
        glTranslated(center.x,center.y,center.z);
        glRotated(90, 1, 0, 0);
        glRotated(this->rotation, 0, 1, 0);

        gluCylinder(cylinder, this->radius, this->radius, .1, 30, 1);
        gluQuadricTexture(topDisk, GL_TRUE);
        gluDisk(topDisk, 0, this->radius, 30, 1);
        gluQuadricTexture(bottomDisk, GL_TRUE);
        gluDisk(bottomDisk, this->radius, 4, 30, 1);
    glPopMatrix();

    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D,0);
}


void Target::update(){
}

void Target::setRotation(double rot){
	this->rotation = rot;
}
