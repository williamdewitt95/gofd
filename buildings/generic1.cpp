#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "../polygon3d.h"
#include "../globals.h"

using std::vector;

const int minFloors = 5;
const int maxFloors = 15;
const double floorHeight = 5;
const double buildingWidth = 40;
const double sidewalkWidth = 3;
const double streetWidth = Building::distanceBetweenBuildings - buildingWidth/2.0;

void createGeneric1Building(vector<Polygon3d> &model, vector<Polygon3d> &boundingBox){
	// == main building ==
	int numFloors = (rand() % (maxFloors - minFloors)) + minFloors;
	{
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		loadTex("textures/bug.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/bug.jpg"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point(  -buildingWidth/2.0, -buildingWidth/2.0,  numFloors*floorHeight));
		points.push_back(Point(  -buildingWidth/2.0, -buildingWidth/2.0,   0));
		points.push_back(Point(   buildingWidth/2.0, -buildingWidth/2.0,   0));
		points.push_back(Point(   buildingWidth/2.0, -buildingWidth/2.0,  numFloors*floorHeight));
		points.push_back(Point(  -buildingWidth/2.0, -buildingWidth/2.0,  numFloors*floorHeight));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		loadTex("textures/bug.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/bug.jpg"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point(   buildingWidth/2.0,  buildingWidth/2.0,  numFloors*floorHeight));
		points.push_back(Point(   buildingWidth/2.0,  buildingWidth/2.0,   0));
		points.push_back(Point(  -buildingWidth/2.0,  buildingWidth/2.0,   0));
		points.push_back(Point(  -buildingWidth/2.0,  buildingWidth/2.0,  numFloors*floorHeight));
		points.push_back(Point(   buildingWidth/2.0,  buildingWidth/2.0,  numFloors*floorHeight));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		loadTex("textures/lain.png");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/lain.png"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point(   buildingWidth/2.0, -buildingWidth/2.0,  numFloors*floorHeight));
		points.push_back(Point(   buildingWidth/2.0, -buildingWidth/2.0,   0));
		points.push_back(Point(   buildingWidth/2.0,  buildingWidth/2.0,   0));
		points.push_back(Point(   buildingWidth/2.0,  buildingWidth/2.0,  numFloors*floorHeight));
		points.push_back(Point(   buildingWidth/2.0, -buildingWidth/2.0,  numFloors*floorHeight));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		loadTex("textures/cloud.png");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/cloud.png"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point(  -buildingWidth/2.0,  buildingWidth/2.0,  numFloors*floorHeight));
		points.push_back(Point(  -buildingWidth/2.0,  buildingWidth/2.0,   0));
		points.push_back(Point(  -buildingWidth/2.0, -buildingWidth/2.0,   0));
		points.push_back(Point(  -buildingWidth/2.0, -buildingWidth/2.0,  numFloors*floorHeight));
		points.push_back(Point(  -buildingWidth/2.0,  buildingWidth/2.0,  numFloors*floorHeight));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	{
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		loadTex("textures/cloud.png");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/cloud.png"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point(  -buildingWidth/2.0,  buildingWidth/2.0,  numFloors*floorHeight));
		points.push_back(Point(  -buildingWidth/2.0, -buildingWidth/2.0,  numFloors*floorHeight));
		points.push_back(Point(   buildingWidth/2.0, -buildingWidth/2.0,  numFloors*floorHeight));
		points.push_back(Point(   buildingWidth/2.0,  buildingWidth/2.0,  numFloors*floorHeight));
		points.push_back(Point(  -buildingWidth/2.0,  buildingWidth/2.0,  numFloors*floorHeight));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}

	boundingBox = model; // copy the simple parts

	// == Sidewalk ==
	{
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		// loadTex("textures/cloud.png");
		// model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/cloud.png"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point(  -buildingWidth/2.0 - sidewalkWidth, -buildingWidth/2.0                ,   0));
		points.push_back(Point(  -buildingWidth/2.0 - sidewalkWidth, -buildingWidth/2.0 - sidewalkWidth,   0));
		points.push_back(Point(   buildingWidth/2.0                , -buildingWidth/2.0 - sidewalkWidth,   0));
		points.push_back(Point(   buildingWidth/2.0                , -buildingWidth/2.0                ,   0));
		points.push_back(Point(  -buildingWidth/2.0 - sidewalkWidth, -buildingWidth/2.0                ,   0));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	Polygon3d sidewalk(model[model.size()-1]);

	Vector rot(0,0,90);
	sidewalk.setRotation(rot);
	sidewalk.setColor(255,125,125);
	model.push_back( sidewalk.getWorldPoints() );

	rot.z = 180;
	sidewalk.setRotation(rot);
	sidewalk.setColor(125,255,125);
	model.push_back( sidewalk.getWorldPoints() );

	rot.z = 270;
	sidewalk.setRotation(rot);
	sidewalk.setColor(125,125,255);
	model.push_back( sidewalk.getWorldPoints() );
}