#include "building.h"

Building::Building(Point center){
	this->center = center;

	//===============================================================================================================
	//we assume that pendulum is of length 1 and then set the scale of the world before we call the draw for the stem
	//===============================================================================================================
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

void Building::draw(){
	glPushMatrix();
	glTranslated(center.x,center.y,center.z);
	for(int x=0; x<sides.size(); x++)
		this->sides[x].draw();
	glPopMatrix();
}
void Building::update(){
}
std::vector<Polygon3d> Building::boundingBox(){
	return this->sides;
}