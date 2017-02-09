#include "tank.h"

Tank::Tank(Point center){
	this->center = center;

	{
		sides.push_back(Polygon3d());
		auto &points = sides[sides.size()-1].getPoints();
		auto &texs = sides[sides.size()-1].getTexturePoints();
		loadTex("bug.jpg");
		sides[sides.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["bug.jpg"].textureRef);
		sides[sides.size()-1].setColor(211,211,211);
		sides[sides.size()-1].setTesselation(true);

		points.push_back(Point(  -1, -1,  1));
		points.push_back(Point(  -1, -1,   0));
		points.push_back(Point(   1, -1,   0));
		points.push_back(Point(   1, -1,  1));
		points.push_back(Point(  -1, -1,  1));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		sides.push_back(Polygon3d());
		auto &points = sides[sides.size()-1].getPoints();
		auto &texs = sides[sides.size()-1].getTexturePoints();
		loadTex("bug.jpg");
		sides[sides.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["bug.jpg"].textureRef);
		sides[sides.size()-1].setColor(211,211,211);
		sides[sides.size()-1].setTesselation(true);

		points.push_back(Point(   1,  1,  1));
		points.push_back(Point(   1,  1,   0));
		points.push_back(Point(  -1,  1,   0));
		points.push_back(Point(  -1,  1,  1));
		points.push_back(Point(   1,  1,  1));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		sides.push_back(Polygon3d());
		auto &points = sides[sides.size()-1].getPoints();
		auto &texs = sides[sides.size()-1].getTexturePoints();
		loadTex("lain.png");
		sides[sides.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["lain.png"].textureRef);
		sides[sides.size()-1].setColor(211,211,211);
		sides[sides.size()-1].setTesselation(true);

		points.push_back(Point(   1, -1,  1));
		points.push_back(Point(   1, -1,   0));
		points.push_back(Point(   1,  1,   0));
		points.push_back(Point(   1,  1,  1));
		points.push_back(Point(   1, -1,  1));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		sides.push_back(Polygon3d());
		auto &points = sides[sides.size()-1].getPoints();
		auto &texs = sides[sides.size()-1].getTexturePoints();
		loadTex("cloud.png");
		sides[sides.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["cloud.png"].textureRef);
		sides[sides.size()-1].setColor(211,211,211);
		sides[sides.size()-1].setTesselation(true);

		points.push_back(Point(  -1,  1,  1));
		points.push_back(Point(  -1,  1,   0));
		points.push_back(Point(  -1, -1,   0));
		points.push_back(Point(  -1, -1,  1));
		points.push_back(Point(  -1,  1,  1));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		sides.push_back(Polygon3d());
		auto &points = sides[sides.size()-1].getPoints();
		auto &texs = sides[sides.size()-1].getTexturePoints();
		loadTex("cloud.png");
		sides[sides.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["cloud.png"].textureRef);
		sides[sides.size()-1].setColor(211,211,211);
		sides[sides.size()-1].setTesselation(true);

		points.push_back(Point(  -1,  -1,  1));
		points.push_back(Point(  -1,  1,   1));
		points.push_back(Point(   1,  1,   1));
		points.push_back(Point(   1, -1,  1));
		points.push_back(Point(  -1,  -1,  1));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
}



void Tank::draw(){
	glPushMatrix();
	glTranslated(tankX, tankY, center.z);
	for(int x=0; x<sides.size(); x++)
		this->sides[x].draw();
	glPopMatrix();
}

void drawTank (void) {
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(tankX, tankY , 0.1);
	glutSolidCube(1);
	glPopMatrix();
}
