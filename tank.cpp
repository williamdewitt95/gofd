#include "globals.h"

Tank::Tank(Point center){
	this->center = center;

	{
		sides.push_back(Polygon3d());
		auto &points = sides[sides.size()-1].getPoints();
		auto &texs = sides[sides.size()-1].getTexturePoints();
		loadTex("bug.jpg");
		sides[sides.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["bug.jpg"].textureRef);
		sides[sides.size()-1].setColor(255,255,255);
		sides[sides.size()-1].setTesselation(true);

		points.push_back(Point(  -5, -5,  20));
		points.push_back(Point(  -5, -5,   0));
		points.push_back(Point(   5, -5,   0));
		points.push_back(Point(   5, -5,  20));
		points.push_back(Point(  -5, -5,  20));
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
		sides[sides.size()-1].setColor(255,255,255);
		sides[sides.size()-1].setTesselation(true);

		points.push_back(Point(   5,  5,  20));
		points.push_back(Point(   5,  5,   0));
		points.push_back(Point(  -5,  5,   0));
		points.push_back(Point(  -5,  5,  20));
		points.push_back(Point(   5,  5,  20));
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
		sides[sides.size()-1].setColor(255,255,255);
		sides[sides.size()-1].setTesselation(true);

		points.push_back(Point(   5, -5,  20));
		points.push_back(Point(   5, -5,   0));
		points.push_back(Point(   5,  5,   0));
		points.push_back(Point(   5,  5,  20));
		points.push_back(Point(   5, -5,  20));
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
		sides[sides.size()-1].setColor(255,255,255);
		sides[sides.size()-1].setTesselation(true);

		points.push_back(Point(  -5,  5,  20));
		points.push_back(Point(  -5,  5,   0));
		points.push_back(Point(  -5, -5,   0));
		points.push_back(Point(  -5, -5,  20));
		points.push_back(Point(  -5,  5,  20));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
}
	vector 

}

void drawTank (void) {
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(tankX, tankY , 0.5);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glRotatef(75, 1.0, 0.0, 0.0);
	glTranslatef(tankX, tankY, 1);
	glutSolidCylinder(0.5, 2, 8, 5);
	glPopMatrix();
}
