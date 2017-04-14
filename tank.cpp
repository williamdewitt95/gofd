#include "globals.h"

#include "tank.h"
#include "building.h"
#include <iostream>
#include <stdio.h>

using std::cout;


Tank::Tank(Point center){
	hitSphereCenter = Point(center.x, center.y, center.z + 1);
	hitSphereRadius = 3.1;

	this->center = center;
	scale = 1;
	baseAngle = 0;
	towerAngle = 0;
	cannonAngle = 0;
	laser = true;
	tankSpeed = 0;
	tankSpeedY = 0;
	tankSpeedX = 0;
	recoilSpeed = 0;
	rollingFriction = 0.0015;
	kineticFriction = 0.005;
	cooldown = 0;
	health = 100;
	tankRecoil = false;
	recoilAngle = 0;
	towerToBaseAngle = 0;

	//Base polygons

	{
		base.push_back(Polygon3d());
		auto &points = base[base.size()-1].getPoints();
		auto &texs = base[base.size()-1].getTexturePoints();
		loadTex("textures/tank/tanktex.jpg");
		base[base.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tanktex.jpg"].textureRef);
		base[base.size()-1].setColor(211,211,211);
		base[base.size()-1].setTesselation(true);

		points.push_back(Point(  -1, -1.5,  1));
		points.push_back(Point(  -1, -1.5,   0));
		points.push_back(Point(   1, -1.5,   0));
		points.push_back(Point(   1, -1.5,  1));
		points.push_back(Point(  -1, -1.5,  1));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		base.push_back(Polygon3d());
		auto &points = base[base.size()-1].getPoints();
		auto &texs = base[base.size()-1].getTexturePoints();
		// loadTex("textures/tank/tanktex.jpg");
		base[base.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tanktex.jpg"].textureRef);
		base[base.size()-1].setColor(211,211,211);
		base[base.size()-1].setTesselation(true);

		points.push_back(Point(   1,  1.5,  1));
		points.push_back(Point(   1,  1.5,   0));
		points.push_back(Point(  -1,  1.5,   0));
		points.push_back(Point(  -1,  1.5,  1));
		points.push_back(Point(   1,  1.5,  1));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		base.push_back(Polygon3d());
		auto &points = base[base.size()-1].getPoints();
		auto &texs = base[base.size()-1].getTexturePoints();
		// loadTex("textures/tank/tanktex.jpg");
		base[base.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tanktex.jpg"].textureRef);
		base[base.size()-1].setColor(211,211,211);
		base[base.size()-1].setTesselation(true);

		points.push_back(Point(   1, -1.5,  1));
		points.push_back(Point(   1, -1.5,   0));
		points.push_back(Point(   1,  1.5,   0));
		points.push_back(Point(   1,  1.5,  1));
		points.push_back(Point(   1, -1.5,  1));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		base.push_back(Polygon3d());
		auto &points = base[base.size()-1].getPoints();
		auto &texs = base[base.size()-1].getTexturePoints();
		// loadTex("textures/tank/tanktex.jpg");
		base[base.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tanktex.jpg"].textureRef);
		base[base.size()-1].setColor(211,211,211);
		base[base.size()-1].setTesselation(true);

		points.push_back(Point(  -1,  1.5,  1));
		points.push_back(Point(  -1,  1.5,   0));
		points.push_back(Point(  -1, -1.5,   0));
		points.push_back(Point(  -1, -1.5,  1));
		points.push_back(Point(  -1,  1.5,  1));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		base.push_back(Polygon3d());
		auto &points = base[base.size()-1].getPoints();
		auto &texs = base[base.size()-1].getTexturePoints();
		// loadTex("textures/tank/tanktex.jpg");
		base[base.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tanktex.jpg"].textureRef);
		base[base.size()-1].setColor(211,211,211);
		base[base.size()-1].setTesselation(true);

		points.push_back(Point(  -1,  -1.5,  1));
		points.push_back(Point(   1, -1.5,  1));
		points.push_back(Point(   1,  1.5,   1));
		points.push_back(Point(  -1,  1.5,   1));
		points.push_back(Point(  -1,  -1.5,  1));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}

	//tower polygons

	{
		tower.push_back(Polygon3d());
		auto &points = tower[tower.size()-1].getPoints();
		auto &texs = tower[tower.size()-1].getTexturePoints();
		loadTex("textures/tank/tanktower.jpg");
		tower[tower.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tanktower.jpg"].textureRef);
		tower[tower.size()-1].setColor(211,211,211);
		tower[tower.size()-1].setTesselation(true);

		points.push_back(Point(  -0.5, -0.5,  1.75));
		points.push_back(Point(  -0.5, -0.5,   1));
		points.push_back(Point(   0.5, -0.5,   1));
		points.push_back(Point(   0.5, -0.5,  1.75));
		points.push_back(Point(  -0.5, -0.5,  1.75));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		tower.push_back(Polygon3d());
		auto &points = tower[tower.size()-1].getPoints();
		auto &texs = tower[tower.size()-1].getTexturePoints();
		// loadTex("textures/tank/tanktower.jpg");
		tower[tower.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tanktower.jpg"].textureRef);
		tower[tower.size()-1].setColor(211,211,211);
		tower[tower.size()-1].setTesselation(true);

		points.push_back(Point(   0.5,  0.5,  1.75));
		points.push_back(Point(   0.5,  0.5,   1));
		points.push_back(Point(  -0.5,  0.5,   1));
		points.push_back(Point(  -0.5,  0.5,  1.75));
		points.push_back(Point(   0.5,  0.5,  1.75));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		tower.push_back(Polygon3d());
		auto &points = tower[tower.size()-1].getPoints();
		auto &texs = tower[tower.size()-1].getTexturePoints();
		// loadTex("textures/tank/tanktower.jpg");
		tower[tower.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tanktower.jpg"].textureRef);
		tower[tower.size()-1].setColor(211,211,211);
		tower[tower.size()-1].setTesselation(true);

		points.push_back(Point(   0.5, -0.5,  1.75));
		points.push_back(Point(   0.5, -0.5,   1));
		points.push_back(Point(   0.5,  0.5,   1));
		points.push_back(Point(   0.5,  0.5,  1.75));
		points.push_back(Point(   0.5, -0.5,  1.75));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		tower.push_back(Polygon3d());
		auto &points = tower[tower.size()-1].getPoints();
		auto &texs = tower[tower.size()-1].getTexturePoints();
		// loadTex("textures/tank/tanktower.jpg");
		tower[tower.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tanktower.jpg"].textureRef);
		tower[tower.size()-1].setColor(211,211,211);
		tower[tower.size()-1].setTesselation(true);

		points.push_back(Point(  -0.5,  0.5,  1.75));
		points.push_back(Point(  -0.5,  0.5,   1));
		points.push_back(Point(  -0.5, -0.5,   1));
		points.push_back(Point(  -0.5, -0.5,  1.75));
		points.push_back(Point(  -0.5,  0.5,  1.75));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		tower.push_back(Polygon3d());
		auto &points = tower[tower.size()-1].getPoints();
		auto &texs = tower[tower.size()-1].getTexturePoints();
		// loadTex("textures/tank/tanktower.jpg");
		tower[tower.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tanktower.jpg"].textureRef);
		tower[tower.size()-1].setColor(211,211,211);
		tower[tower.size()-1].setTesselation(true);

		points.push_back(Point(  -0.5,  -0.5,  1.75));
		points.push_back(Point(   0.5, -0.5,  1.75));
		points.push_back(Point(   0.5,  0.5,   1.75));
		points.push_back(Point(  -0.5,  0.5,   1.75));
		points.push_back(Point(  -0.5,  -0.5,  1.75));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}

	//Cannon polygons

		{
		cannon.push_back(Polygon3d());
		auto &points = cannon[cannon.size()-1].getPoints();
		auto &texs = cannon[cannon.size()-1].getTexturePoints();
		loadTex("textures/tank/tankcannon.jpg");
		cannon[cannon.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tankcannon.jpg"].textureRef);
		cannon[cannon.size()-1].setColor(211,211,211);
		cannon[cannon.size()-1].setTesselation(true);

		points.push_back(Point(  -0.125, 0.5,  1.5));
		points.push_back(Point(  -0.125, 0.5,  1.25));
		points.push_back(Point(  0.125, 0.5,  1.25));
		points.push_back(Point(  0.125, 0.5,  1.5));
		points.push_back(Point(  -0.125, 0.5,  1.5));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		cannon.push_back(Polygon3d());
		auto &points = cannon[cannon.size()-1].getPoints();
		auto &texs = cannon[cannon.size()-1].getTexturePoints();
		// loadTex("textures/tank/tankcannon.jpg");
		cannon[cannon.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tankcannon.jpg"].textureRef);
		cannon[cannon.size()-1].setColor(211,211,211);
		cannon[cannon.size()-1].setTesselation(true);

		points.push_back(Point(  0.125, 2.25,  1.5));
		points.push_back(Point(  0.125, 2.25,  1.25));
		points.push_back(Point(  -0.125, 2.25,  1.25));
		points.push_back(Point(  -0.125, 2.25,  1.5));
		points.push_back(Point(  0.125, 2.25,  1.5));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		cannon.push_back(Polygon3d());
		auto &points = cannon[cannon.size()-1].getPoints();
		auto &texs = cannon[cannon.size()-1].getTexturePoints();
		// loadTex("textures/tank/tankcannon.jpg");
		cannon[cannon.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tankcannon.jpg"].textureRef);
		cannon[cannon.size()-1].setColor(211,211,211);
		cannon[cannon.size()-1].setTesselation(true);

		points.push_back(Point(  0.125, 0.5,  1.5));
		points.push_back(Point(  0.125, 0.5,  1.25));
		points.push_back(Point(  0.125, 2.25,  1.25));
		points.push_back(Point(  0.125, 2.25,  1.5));
		points.push_back(Point(  0.125, 0.5,  1.5));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		cannon.push_back(Polygon3d());
		auto &points = cannon[cannon.size()-1].getPoints();
		auto &texs = cannon[cannon.size()-1].getTexturePoints();
		// loadTex("textures/tank/tankcannon.jpg");
		cannon[cannon.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tankcannon.jpg"].textureRef);
		cannon[cannon.size()-1].setColor(211,211,211);
		cannon[cannon.size()-1].setTesselation(true);

		points.push_back(Point(  -0.125, 2.25,  1.5));
		points.push_back(Point(  -0.125, 2.25,  1.25));
		points.push_back(Point(  -0.125, 0.5,  1.25));
		points.push_back(Point(  -0.125, 0.5,  1.5));
		points.push_back(Point(  -0.125, 2.25,  1.5));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		cannon.push_back(Polygon3d());
		auto &points = cannon[cannon.size()-1].getPoints();
		auto &texs = cannon[cannon.size()-1].getTexturePoints();
		// loadTex("textures/tank/tankcannon.jpg");
		cannon[cannon.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tankcannon.jpg"].textureRef);
		cannon[cannon.size()-1].setColor(211,211,211);
		cannon[cannon.size()-1].setTesselation(true);

		points.push_back(Point(  -0.125, 0.5,  1.5));
		points.push_back(Point(  0.125, 0.5,  1.5));
		points.push_back(Point(  0.125, 2.25,  1.5));
		points.push_back(Point(  -0.125, 2.25,  1.5));
		points.push_back(Point(  -0.125, 0.5,  1.5));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		cannon.push_back(Polygon3d());
		auto &points = cannon[cannon.size()-1].getPoints();
		auto &texs = cannon[cannon.size()-1].getTexturePoints();
		// loadTex("textures/tank/tankcannon.jpg");
		cannon[cannon.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tankcannon.jpg"].textureRef);
		cannon[cannon.size()-1].setColor(211,211,211);
		cannon[cannon.size()-1].setTesselation(true);

		points.push_back(Point(  -0.125, 0.5,  1.25));
		points.push_back(Point(  -0.125, 2.25,  1.25));
		points.push_back(Point(  0.125, 2.25,  1.25));
		points.push_back(Point(  0.125, 0.5,  1.25));
		points.push_back(Point(  -0.125, 0.5,  1.25));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	
	baseBoundingBox=base; // use these to provide our bounding box
	towerBoundingBox=tower;
	cannonBoundingBox=cannon;
}



void Tank::draw(){
	glPushMatrix();
		glTranslated(center.x, center.y, center.z);
		glScaled(scale, scale, scale);
		glRotated(baseAngle, 0, 0, 1);
		for(int x=0; x<base.size(); x++)
			this->base[x].draw();
	glPopMatrix();//When we rotate the base, let the turret stay on target

	glPushMatrix();
		glTranslated(center.x, center.y, center.z);
		glRotated(towerAngle, 0, 0, 1);
		for(int x=0; x<tower.size(); x++)
			this->tower[x].draw();
		glPushMatrix();
			glTranslated(0, 0.5, 1.375);
			if (cannonAngle > 75)
				cannonAngle = 75;
			else if (cannonAngle < -10)
				cannonAngle = -10;
			glRotated(cannonAngle, 1, 0, 0);
			glTranslated(0, -0.5, -1.375);
			//draw a laser guide
			if (laser) {
				glLineWidth(5);
				glColor4f(1.0 ,0.0 ,0.0 ,1.0);
				glBegin(GL_LINES);
					glVertex3f(0, 0.5, 1.375);
					glVertex3f(0, 2000, 1.375);
				glEnd();
				glColor4f(1.0 ,1.0 ,1.0 ,1.0);
				glLineWidth(1);
			}
			for(int x=0; x<cannon.size(); x++)
				this->cannon[x].draw();
		glPopMatrix();
	glPopMatrix();
}

void Tank::update(double tankBaseRotate, double tankTurretRotate, double tankCannonRotate, int cameraMode, double tankAccel){
	
	//max speed limit
	if (((this->tankSpeedY < 0.15) && (tankAccel > 0)) || ((this->tankSpeedY > -0.15) && (tankAccel < 0)))  {
		this->tankSpeedY += tankAccel;
	}

	//apply friction
	if (this->tankSpeedY > 0) {
		this->tankSpeedY -= rollingFriction;
		if (this->tankSpeedY < 0)
			this->tankSpeedY = 0;
	}
	if (this->tankSpeedY < 0) {
		this->tankSpeedY += rollingFriction;
		if (this->tankSpeedY > 0)
			this->tankSpeedY = 0;
	}

	if (this->tankSpeedX > 0) {
		this->tankSpeedX -= kineticFriction;
		if (this->tankSpeedX < 0)
			this->tankSpeedX = 0;
	}
	if (this->tankSpeedX < 0) {
		this->tankSpeedX += kineticFriction;
		if (this->tankSpeedX > 0)
			this->tankSpeedX = 0;
	}

	//limit recoil speed
	if (this->tankSpeedY > 0.20) {
		this->tankSpeedY -= 2*rollingFriction;
		if (this->tankSpeedY < 0)
			this->tankSpeedY = 0;
	}
	if (this->tankSpeedY < -0.20) {
		this->tankSpeedY += 2*rollingFriction;
		if (this->tankSpeedY > 0)
			this->tankSpeedY = 0;
	}
	//cout << "tankSpeed = " << tankSpeed << "\n";

	//translate for recoil
	if (tankRecoil) {
		//angle between tower and base is towerToBaseAngle

		this->tankSpeedX += recoilSpeed * sin(towerToBaseAngle * (M_PI / 180));
		this->tankSpeedY -= recoilSpeed * cos(towerToBaseAngle * (M_PI / 180));

		//cout << "recoilSpeed = " << recoilSpeedY << "\n";
		tankRecoil = false;
	}

	double newX = this->center.x + this->tankSpeedY * cos((this->baseAngle + 90) * (M_PI / 180));
	double newY = this->center.y + this->tankSpeedY * sin((this->baseAngle + 90) * (M_PI / 180));

	newX += this->tankSpeedX * cos((this->baseAngle) * (M_PI / 180));
	newY += this->tankSpeedX * sin((this->baseAngle) * (M_PI / 180));

	if(onLock(newX,newY)){
		this->center.x = newX;
		this->center.y = newY;
	}

	if ((this->baseAngle > 360) || (this->baseAngle < -360))
		this->baseAngle = 0;
	this->baseAngle += tankBaseRotate;
	// this->towerAngle += tankTurretRotate;
	// this->cannonAngle += tankCannonRotate;
	cameraMovement(GLOBAL.WINDOW_MAX_X/2,GLOBAL.WINDOW_MAX_Y-(GLOBAL.WINDOW_MAX_Y/2),this->center, cameraMode);//keep camera synced to mouse movements
	this->turretFollowMouse(GLOBAL.WINDOW_MAX_X/2,GLOBAL.WINDOW_MAX_Y-(GLOBAL.WINDOW_MAX_Y/2), cameraMode);//keep turret synced to mouse movements

	if(this->cooldown > 0)
		this->cooldown--;
}

void Tank::turretFollowMouse(int x, int y, int cameraMode){//Turret + cannon follow the mouse cursor

	double movementDivisor = 6.0;
	//x and y are window cordinates
	//it is up to us to get deltas
	y=GLOBAL.WINDOW_MAX_Y-y;
	int midX = GLOBAL.WINDOW_MAX_X/2;
	int midY = GLOBAL.WINDOW_MAX_Y/2;

	int dx = x-midX;
	int dy = y-midY;

	double angleH = GLOBAL.CAMERA_ANGLE_HORIZONTAL;
	double angleV = GLOBAL.CAMERA_ANGLE_VERTICAL;
	angleH += dx/movementDivisor;
	if(angleH>360)angleH-=360;
	if(angleH<0)angleH+=360;
	angleV += dy/movementDivisor;
	if(angleV>70)angleV=70;
	if(angleV<-10)angleV=-10;

	// we will have a length of 5 for the line in the XY plane
	// bool firstPerson = false;//for rapid testing of different cameras
	if(cameraMode==0){
		this->towerAngle = this->towerAngle;
		this->cannonAngle = this->cannonAngle;
	}
	else if(cameraMode == 1){
		this->towerAngle = -1.0*angleH-90.0;//turret follows
		this->cannonAngle = angleV;
	}
	else{
		
		this->towerAngle = -1.0*angleH+90.0;
		this->cannonAngle = angleV; 	
	}

	if(dx==0 && dy==0)
		return; //we are not really doing anything, so we will simply ignore this thing
}

bool Tank::onLock(int x, int y){//Returns a bool stating if the coordinate is in the grid or not
	double min = -(Building::maxBuildingWidth/2 + Building::sidewalkWidth);
	double max =  (NUM_BLOCKS_WIDE - 1)*(Building::distanceBetweenBuildings) - min;

	if (min <= x && x <= max && min <= y && y <= max) return 1;
	else return 0;
}


std::vector<Polygon3d> Tank::boundingBox(void){
	//every time someone needs the polygons for our bounding box, we have to make it from scratch
	//we start out with having the starting polygons for the tank in the default positions
	//we need to set the rotation for all of them and then put them into a single list

	std::vector<Polygon3d> temp;
	Vector baseRot(0,0,baseAngle);
	Vector towerRot(0,0,towerAngle);
	Vector cannonRot(0,0,cannonAngle);

	for(int x=0; x < baseBoundingBox.size(); x++){
		baseBoundingBox[x].setRotation(baseRot);
		temp.push_back(baseBoundingBox[x]);
	}
	for(int x=0; x < towerBoundingBox.size(); x++){
		towerBoundingBox[x].setRotation(towerRot);
		temp.push_back(towerBoundingBox[x]);
	}
	for(int x=0; x < cannonBoundingBox.size(); x++){
		cannonBoundingBox[x].setRotation(cannonRot);
		temp.push_back(cannonBoundingBox[x]);
	}
	return temp;
}

void Tank::drawScore(){
	int score = 40;
	glPushMatrix();

		int i, len;
		char label[] = "Score: ";
		void *font = GLUT_STROKE_ROMAN;

		glTranslatef(82, 90, 0);
		glScalef(0.15, 0.15, 0.15);

		glPushMatrix();
			glColor3f(1.0,1.0,1.0);
			glRotatef(180.0,1.0,0.0,0.0);
			glScalef(0.125,0.125,0.125);
			glTranslatef(-550.0, 100, 0);
			len = (int) strlen(label);
			for(i = 0;i<len;i++)
				glutStrokeCharacter(font, label[i]);

			std::ostringstream printNum;
			std::string printy;

			printNum << score;
			printy = printNum.str();
			len = (int) strlen(&printy[0]);
			for(i = 0;i<len;i++)
				glutStrokeCharacter(font,printy[i]);

			printNum.str("");
		glPopMatrix();
	glPopMatrix();
}

void Tank::drawCooldownBar(){
	glPushMatrix();

	int i, len;
	char label[] = "Cooldown";
	void *font = GLUT_STROKE_ROMAN;

	glTranslatef(82, 90, 0);
	glScalef(0.15, 0.15, 0.15);

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glRotatef(180.0,1.0,0.0,0.0);
	glScalef(0.125,0.125,0.125);
	glTranslatef(-550.0, -100, 0);
	len = (int) strlen(label);
	for(i = 0;i<len;i++)
		glutStrokeCharacter(font, label[i]);

	glPopMatrix();
	
	glBegin(GL_POLYGON);
		//draw remaining cooldown time
		glColor3ub(255,255,255);
		glVertex2f(0.0,0.0);
		glVertex2f(0.0,20.0);
		glVertex2f((float) (this->cooldown/100.0)*100.0, 20.0);
		glVertex2f((float) (this->cooldown/100.0)*100.0,  0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
		
		//draw missing cooldown time
		glColor3ub(0,0,200);
		glVertex2f((float) (this->cooldown/100.0)*100.0,  0.0);
		glVertex2f((float) (this->cooldown/100.0)*100.0, 20.0);
		glVertex2f(100.0,20.0);
		glVertex2f(100.0,0.0);
	glEnd();

	glPopMatrix();
}

void Tank::drawHealthBar(){
	glPushMatrix();

		int i, len;
		char healthLabel[] = "Health";
		void *font = GLUT_STROKE_ROMAN;

		glTranslatef(82, 95, 0);
		glScalef(0.15, 0.15, 0.15);

		glPushMatrix();
			glColor3f(1.0,1.0,1.0);
			glRotatef(180.0,1.0,0.0,0.0);
			glScalef(0.125,0.125,0.125);
			glTranslatef(-400, -130, 0);
			len = (int) strlen(healthLabel);
			for(i = 0;i<len;i++)
				glutStrokeCharacter(font, healthLabel[i]);

		glPopMatrix();
		
		glBegin(GL_POLYGON);
			//draw remaining health
			glColor3ub(0,255,0);
			glVertex2f(0.0,0.0);
			glVertex2f(0.0,20.0);
			glVertex2f((float) (this->health/100.0)*100.0, 20.0);
			glVertex2f((float) (this->health/100.0)*100.0,  0.0);
		glEnd();
		
		glBegin(GL_POLYGON);
			
			//draw missing heath bar
			glColor3ub(255,0,0);
			glVertex2f((float) (this->health/100.0)*100.0,  0.0);
			glVertex2f((float) (this->health/100.0)*100.0, 20.0);
			glVertex2f(100.0,20.0);
			glVertex2f(100.0,0.0);
		glEnd();

	glPopMatrix();
}
void Tank::shoot() {
	if(this->cooldown>0){//true  = we are still in cooldown
		return ;
	}
	double x = this->center.x + -1*(2.25-sin(cannonAngle*M_PI/180.0)) * sin(this->towerAngle*M_PI/180.0); 
	double y = this->center.y + (2.25-sin(cannonAngle*M_PI/180.0)) * cos(this->towerAngle*M_PI/180.0); 
	double z = this->center.z + 1.375 + 1.75*sin(this->cannonAngle*M_PI/180.0);
	// printf("%.3f\n",z);


	projectiles.push_back(new Projectile(Point(x,y,z), Point(x,y,z), this->cannonAngle, this->towerAngle+90));
	this->cooldown = 100;
	// return projectile;

	applyRecoil();
}

void Tank::applyRecoil() {
	tankRecoil = true;
	recoilSpeed = 0.17;
	recoilAngle = this->towerAngle + 90;
	towerToBaseAngle = (this->towerAngle + 90) - (this->baseAngle + 90);
}
