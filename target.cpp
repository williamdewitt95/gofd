#include "target.h"
#include "globals.h"
#include <stdlib.h>

Target::Target(Point center)
{
    this->center = center;
    this->radius = 3;
    this->rotation = 0;
    int choice = rand() % 9;
    if(choice == 0)
    {
    	loadTex("textures/mascots/woffordterriers.png");
    	this->mascotChoice = GLOBAL.TEXTURES_LOADED["textures/mascots/woffordterriers.png"].textureRef;
	}
	else if (choice == 1)
	{
    	loadTex("textures/mascots/citadelbulldogs.png");
    	this->mascotChoice = GLOBAL.TEXTURES_LOADED["textures/mascots/citadelbulldogs.png"].textureRef;
    }
	else if (choice == 2)
	{
    	loadTex("textures/mascots/chattanoogamocs.png");
    	this->mascotChoice = GLOBAL.TEXTURES_LOADED["textures/mascots/chattanoogamocs.png"].textureRef;
    }
	else if (choice == 3)
	{
    	loadTex("textures/mascots/furmanpaladins.png");
    	this->mascotChoice = GLOBAL.TEXTURES_LOADED["textures/mascots/furmanpaladins.png"].textureRef;
    }
	else if (choice == 4)
	{
    	loadTex("textures/mascots/samfordbulldogs.png");
    	this->mascotChoice = GLOBAL.TEXTURES_LOADED["textures/mascots/samfordbulldogs.png"].textureRef;
    }
	else if (choice == 5)
	{
    	loadTex("textures/mascots/uncgspartans.png");
    	this->mascotChoice = GLOBAL.TEXTURES_LOADED["textures/mascots/uncgspartans.png"].textureRef;
    }
	else if (choice == 6)
	{
    	loadTex("textures/mascots/vmilogo.png");
    	this->mascotChoice = GLOBAL.TEXTURES_LOADED["textures/mascots/vmilogo.png"].textureRef;
    }
	else if (choice == 7)
	{
    	loadTex("textures/mascots/wcucatamounts.png");
    	this->mascotChoice = GLOBAL.TEXTURES_LOADED["textures/mascots/wcucatamounts.png"].textureRef;
    }
	else if (choice == 8)
	{
    	loadTex("textures/mascots/etsubucs.png");
    	this->mascotChoice = GLOBAL.TEXTURES_LOADED["textures/mascots/etsubucs.png"].textureRef;
    }

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

    glBindTexture(GL_TEXTURE_2D,this->mascotChoice);

    glPushMatrix();
        glTranslated(center.x,center.y,center.z);
        glRotated(90, 1, 0, 0);
        glRotated(180,0, 0, 1);
        glRotated(this->rotation, 0, 1, 0);

        gluCylinder(cylinder, this->radius, this->radius, .1, 30, 1);
        gluQuadricTexture(topDisk, GL_TRUE);
        gluDisk(topDisk, 0, this->radius, 30, 1);
        glRotated(180, 0, 1, 0);
        gluQuadricTexture(bottomDisk, GL_TRUE);
        gluDisk(bottomDisk, 0, this->radius, 30, 1);
    glPopMatrix();

    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D,0);
}


void Target::update(){
}

void Target::setRotation(double rot){
	this->rotation = rot;
}
