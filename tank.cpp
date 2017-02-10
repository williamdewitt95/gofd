#include "tank.h"

Tank::Tank(Point center){
	this->center = center;
	scale = 1;

	//Base polygons

	{
		base.push_back(Polygon3d());
		auto &points = base[base.size()-1].getPoints();
		auto &texs = base[base.size()-1].getTexturePoints();
		loadTex("tanktex.png");
		base[base.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.png"].textureRef);
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
		loadTex("tanktex.png");
		base[base.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.png"].textureRef);
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
		loadTex("tanktex.png");
		base[base.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.png"].textureRef);
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
		loadTex("tanktex.png");
		base[base.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.png"].textureRef);
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
		loadTex("tanktex.png");
		base[base.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.png"].textureRef);
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
		loadTex("tanktex.png");
		tower[tower.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.png"].textureRef);
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
		loadTex("tanktex.png");
		tower[tower.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.png"].textureRef);
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
		loadTex("tanktex.png");
		tower[tower.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.png"].textureRef);
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
		loadTex("tanktex.png");
		tower[tower.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.png"].textureRef);
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
		loadTex("tanktex.png");
		tower[tower.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.png"].textureRef);
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
		loadTex("tanktex.png");
		cannon[cannon.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.png"].textureRef);
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
		loadTex("tanktex.png");
		cannon[cannon.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.png"].textureRef);
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
		loadTex("tanktex.png");
		cannon[cannon.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.png"].textureRef);
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
		loadTex("tanktex.png");
		cannon[cannon.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.png"].textureRef);
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
		loadTex("tanktex.png");
		cannon[cannon.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["tanktex.png"].textureRef);
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
}



void Tank::draw(){
	glPushMatrix();
	glTranslated(center.x, center.y, center.z);
	glRotated(angle, 0, 0, 1);
	glScaled(scale, scale, scale);
	for(int x=0; x<base.size(); x++)
		this->base[x].draw();
	for(int x=0; x<tower.size(); x++)
		this->tower[x].draw();
	for(int x=0; x<cannon.size(); x++)
		this->cannon[x].draw();
	glPopMatrix();
}

void Tank::update(){
}
std::vector<Polygon3d> Tank::boundingBox(){
	return this->base;
}