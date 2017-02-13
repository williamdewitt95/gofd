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

	//Base polygons

	{
		base.push_back(Polygon3d());
		auto &points = base[base.size()-1].getPoints();
		auto &texs = base[base.size()-1].getTexturePoints();
		loadTex("tanktex.jpg");
		base[base.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.jpg"].textureRef);
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
		loadTex("tanktex.jpg");
		base[base.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.jpg"].textureRef);
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
		loadTex("tanktex.jpg");
		base[base.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.jpg"].textureRef);
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
		loadTex("tanktex.jpg");
		base[base.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.jpg"].textureRef);
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
		loadTex("tanktex.jpg");
		base[base.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.jpg"].textureRef);
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
		loadTex("tanktower.jpg");
		tower[tower.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktower.jpg"].textureRef);
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
		loadTex("tanktower.jpg");
		tower[tower.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktower.jpg"].textureRef);
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
		loadTex("tanktower.jpg");
		tower[tower.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktower.jpg"].textureRef);
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
		loadTex("tanktower.jpg");
		tower[tower.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktower.jpg"].textureRef);
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
		loadTex("tanktower.jpg");
		tower[tower.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktower.jpg"].textureRef);
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
		loadTex("tankcannon.jpg");
		cannon[cannon.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tankcannon.jpg"].textureRef);
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
		loadTex("tankcannon.jpg");
		cannon[cannon.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tankcannon.jpg"].textureRef);
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
		loadTex("tankcannon.jpg");
		cannon[cannon.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tankcannon.jpg"].textureRef);
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
		loadTex("tankcannon.jpg");
		cannon[cannon.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tankcannon.jpg"].textureRef);
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
		loadTex("tankcannon.jpg");
		cannon[cannon.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tankcannon.jpg"].textureRef);
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
		loadTex("tankcannon.jpg");
		cannon[cannon.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tankcannon.jpg"].textureRef);
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
}



void Tank::draw(){
	//cout << baseAngle << "\n";

	glPushMatrix();
	glTranslated(center.x, center.y, center.z);
	glScaled(scale, scale, scale);
	glRotated(baseAngle, 0, 0, 1);
	for(int x=0; x<base.size(); x++)
		this->base[x].draw();
	glPushMatrix();
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
	glPopMatrix();
}

void Tank::update(){
}
std::vector<Polygon3d> Tank::boundingBox(){
	return this->base;
}

void Tank::shoot() {}
