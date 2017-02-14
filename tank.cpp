#include "tank.h"
#include <iostream>
using std::cout;


Tank::Tank(Point center){
	this->center = center;
	scale = 1;
	baseAngle = 0;
	towerAngle = 0;
	cannonAngle = 0;
	laser = true;
	tankSpeed = 0;

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
		loadTex("textures/tank/tanktex.jpg");
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
		loadTex("textures/tank/tanktex.jpg");
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
		loadTex("textures/tank/tanktex.jpg");
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
		loadTex("textures/tank/tanktex.jpg");
		base[base.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tanktex.jpg"].textureRef);
		base[base.size()-1].setColor(211,211,211);
		base[base.size()-1].setTesselation(true);

		points.push_back(Point(  -1,  -1.5,  1));
		points.push_back(Point(  -1,  1.5,   1));
		points.push_back(Point(   1,  1.5,   1));
		points.push_back(Point(   1, -1.5,  1));
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
		loadTex("textures/tank/tanktower.jpg");
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
		loadTex("textures/tank/tanktower.jpg");
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
		loadTex("textures/tank/tanktower.jpg");
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
		loadTex("textures/tank/tanktower.jpg");
		tower[tower.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tanktower.jpg"].textureRef);
		tower[tower.size()-1].setColor(211,211,211);
		tower[tower.size()-1].setTesselation(true);

		points.push_back(Point(  -0.5,  -0.5,  1.75));
		points.push_back(Point(  -0.5,  0.5,   1.75));
		points.push_back(Point(   0.5,  0.5,   1.75));
		points.push_back(Point(   0.5, -0.5,  1.75));
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
		loadTex("textures/tank/tankcannon.jpg");
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
		loadTex("textures/tank/tankcannon.jpg");
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
		loadTex("textures/tank/tankcannon.jpg");
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
		loadTex("textures/tank/tankcannon.jpg");
		cannon[cannon.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/tank/tankcannon.jpg"].textureRef);
		cannon[cannon.size()-1].setColor(211,211,211);
		cannon[cannon.size()-1].setTesselation(true);

		points.push_back(Point(  -0.125, 0.5,  1.5));
		points.push_back(Point(  -0.125, 2.25,  1.5));
		points.push_back(Point(  0.125, 2.25,  1.5));
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
		loadTex("textures/tank/tankcannon.jpg");
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
	
	totalBoundingBox.push_back(base);
	totalBoundingBox.push_back(tower);
	totalBoundingBox.push_back(cannon);
}



void Tank::draw(){
	// cout << baseAngle << "\n";

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

void Tank::update(double tankSpeed, double tankBaseRotate, double tankTurretRotate, double tankCannonRotate, int cameraMode){
	this->center.x += tankSpeed * cos((this->baseAngle + 90) * (M_PI / 180));
	this->center.y += tankSpeed * sin((this->baseAngle + 90) * (M_PI / 180));
	if ((this->baseAngle > 360) || (this->baseAngle < -360))
		this->baseAngle = 0;
	this->baseAngle += tankBaseRotate;
	// this->towerAngle += tankTurretRotate;
	// this->cannonAngle += tankCannonRotate;
	cameraMovement(GLOBAL.WINDOW_MAX_X/2,GLOBAL.WINDOW_MAX_Y/2,this->center, cameraMode);//keep camera synced to mouse movements
	this->turretFollowMouse(GLOBAL.WINDOW_MAX_X/2, GLOBAL.WINDOW_MAX_Y/2, cameraMode);//keep turret synced to mouse movements


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
		this->towerAngle = -1*angleH-90;//turret follows
		this->cannonAngle = angleV;
	}
	else{
		
		this->towerAngle = -1*angleH+90;
		this->cannonAngle = 60-angleV; 	
	}

	

	if(dx==0 && dy==0)
		return; //we are not really doing anything, so we will simply ignore this thing

	// printf("PassiveFunc\t%dx%d\n",dx,dy); // pixel deltas
	// printf("PassiveFunc\t%f %f\n",angleH,angleV); // look angles
	// printf("PassiveFunc\n%.2f %.2f %.2f\n",cameraLook.x,cameraLook.y,cameraLook.z); // look vector

}



std::vector< std::vector<Polygon3d> > Tank::boundingBox(void){
	return this->totalBoundingBox;
}

void Tank::shoot() {}
