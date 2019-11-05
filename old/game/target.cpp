#include "target.h"
#include "globals.h"

Target::Target(Point center)
{
    this->center = center;
    this->radius = 3;
    this->rotation = 0;
    this->state = NORMAL;
    int choice = rand() % 9;
    //Everyone from the Southern Conference except mercer. Of course we'll blow them up and stuff.
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
        points.push_back(Point(-radius,0,-radius));
        points.push_back(Point( radius,0,-radius));
        points.push_back(Point( radius,0, radius));
        points.push_back(Point(-radius,0, radius));
        points.push_back(Point(-radius,0,-radius));
    }

    {
        boundingBox.push_back(Polygon3d());
        auto &points = boundingBox[boundingBox.size()-1].getPoints();
        points.push_back(Point(  radius,  0, -radius));
        points.push_back(Point(  radius, .1, -radius));
        points.push_back(Point(  radius, .1,  radius));
        points.push_back(Point(  radius,  0,  radius));
        points.push_back(Point(  radius,  0, -radius));
    }

    {
        boundingBox.push_back(Polygon3d());
        auto &points = boundingBox[boundingBox.size()-1].getPoints();
        points.push_back(Point( -radius,  0,  radius));
        points.push_back(Point( -radius, .1,  radius));
        points.push_back(Point(  radius, .1,  radius));
        points.push_back(Point(  radius,  0,  radius));
        points.push_back(Point( -radius,  0,  radius));
    }

    {
        boundingBox.push_back(Polygon3d());
        auto &points = boundingBox[boundingBox.size()-1].getPoints();
        points.push_back(Point( -radius,  0, -radius));
        points.push_back(Point( -radius, .1, -radius));
        points.push_back(Point(  radius, .1, -radius));
        points.push_back(Point(  radius,  0, -radius));
        points.push_back(Point( -radius,  0, -radius));
    }

    {
        boundingBox.push_back(Polygon3d());
        auto &points = boundingBox[boundingBox.size()-1].getPoints();
        points.push_back(Point( -radius,  0, -radius));
        points.push_back(Point( -radius, .1, -radius));
        points.push_back(Point( -radius, .1,  radius));
        points.push_back(Point( -radius,  0,  radius));
        points.push_back(Point( -radius,  0, -radius));
    }

    {
        boundingBox.push_back(Polygon3d());
        auto &points = boundingBox[boundingBox.size()-1].getPoints();
        points.push_back(Point( -radius, .1, -radius));
        points.push_back(Point(  radius, .1, -radius));
        points.push_back(Point(  radius, .1,  radius));
        points.push_back(Point( -radius, .1,  radius));
        points.push_back(Point( -radius, .1, -radius));
    }
    for(int x=0; x<boundingBox.size(); x++){
        boundingBox[x].setCenter(center);
    }
}

void Target::draw(){
    //Do not draw us if we are already hit
    if(this->state == DEAD)
        return;

    glPushMatrix();

    // glTranslated(center.x,center.y,center.z);
    // glRotated(90, 1, 0, 0);
    // glRotated(this->rotation, 0, 1, 0);

    // I used disks disk to generate the target.
    GLUquadricObj *cylinder = gluNewQuadric();
    GLUquadricObj *topDisk = gluNewQuadric();
    GLUquadricObj *bottomDisk = gluNewQuadric();
    gluQuadricDrawStyle(cylinder, GLU_FILL);

    glBindTexture(GL_TEXTURE_2D,this->mascotChoice);
    glColor3ub(255,255,255); // make it white so the texture is always perfect

    glPushMatrix();
        glTranslated(center.x,center.y,center.z);
        glRotated(90, 1, 0, 0);
        glRotated(180, 0, 0, 1);
        glRotated(this->rotation, 0, 1, 0);

        //Drawing and texturing a disk works a little differently, but is still very simple
        //A quadric object is created as a pointer, then fed into the proper
        //quadrick draw function. Objects seen above, function seen below.
        gluCylinder(cylinder, this->radius, this->radius, .1, 30, 1);
        //Takes the active texture and applies it linearly to the object.
        gluQuadricTexture(topDisk, GL_TRUE);
        gluDisk(topDisk, 0, this->radius, 30, 1);
        glRotated(180, 0, 1, 0);
        gluQuadricTexture(bottomDisk, GL_TRUE);
        gluDisk(bottomDisk, 0, this->radius, 30, 1);
    glPopMatrix();

    gluDeleteQuadric(cylinder);
    gluDeleteQuadric(topDisk);
    gluDeleteQuadric(bottomDisk);

    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D,0);
}

void Target::draw_map_marker(){
    //Do not draw us if we are already hit
    if(this->state == DEAD)
        return;

    glBindTexture(GL_TEXTURE_2D,this->mascotChoice);
    glColor3ub(255,255,255); // make it white so the texture is always perfect

    GLUquadricObj *topDisk = gluNewQuadric();

    glPushMatrix();
        glTranslated(center.x,center.y,200);
        glRotated(180, 0, 0, 1);

        gluQuadricTexture(topDisk, GL_TRUE);
        gluDisk(topDisk, 0, this->radius*4, 30, 1);
    glPopMatrix();

    gluDeleteQuadric(topDisk);
    glBindTexture(GL_TEXTURE_2D,0);
}

//Originally for the spinning targets, these would set the rotation of the targets. However, spinning was removed
//So this function is an artifact.
void Target::update(){
}

void Target::setRotation(double rot){
	this->rotation = rot;
    for(int x=0; x<boundingBox.size(); x++){
        Vector temp(0,0,rot);
        boundingBox[x].setRotation(temp);
    }
}
