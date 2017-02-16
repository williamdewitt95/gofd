#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include "../polygon3d.h"
#include "../globals.h"

using std::vector;

void createGenericOctogonBuilding(vector<Polygon3d> &model, vector<Polygon3d> &boundingBox){
	const int minFloors = 12;
	const int maxFloors = 20;
	const double floorHeight = 5;
	const double buildingWidth = Building::maxBuildingWidth;
	const double streetWidth = Building::streetWidth;

	double distFromCenter = buildingWidth/2.0;
	double wallHalfWidth = tan(M_PI/8.0) * distFromCenter;
	double sidewalkHalfWidth = tan(M_PI/8.0) * (distFromCenter + Building::sidewalkWidth);

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

		points.push_back(Point(  -wallHalfWidth, -distFromCenter,  numFloors*floorHeight));
		points.push_back(Point(  -wallHalfWidth, -distFromCenter,   0));
		points.push_back(Point(   wallHalfWidth, -distFromCenter,   0));
		points.push_back(Point(   wallHalfWidth, -distFromCenter,  numFloors*floorHeight));
		points.push_back(Point(  -wallHalfWidth, -distFromCenter,  numFloors*floorHeight));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	//now we copy the known good side and rotate it around the Z axis to put it into place
	Polygon3d singleSide(model[model.size()-1]);
	Vector rot;
	for(int x=1; x<8; x++){
		rot.z = 45 * x;
		singleSide.setRotation(rot);
		model.push_back( singleSide.getWorldPoints() );
	}

	{ // the top
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		loadTex("textures/cloud.png");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/cloud.png"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		Point firstPolyPoint(-distFromCenter, wallHalfWidth, numFloors*floorHeight); // we have this as the first point and simply rotate it around

		for(int x=0; x<=8; x++){ // gives 9 points with the first and last being repeated
			points.push_back(firstPolyPoint.rotatePoint(45*x,0,0,1));
		}

		texs.push_back(Point(   0    , 1.0/3.0 , 0));
		texs.push_back(Point(   0    , 2.0/3.0 , 0));
		texs.push_back(Point(1.0/3.0 ,   1.0   , 0));
		texs.push_back(Point(2.0/3.0 ,   1.0   , 0));
		texs.push_back(Point(  1.0   , 2.0/3.0 , 0));
		texs.push_back(Point(  1.0   , 1.0/3.0 , 0));
		texs.push_back(Point(2.0/3.0 ,    0    , 0));
		texs.push_back(Point(1.0/3.0 ,    0    , 0));
		texs.push_back(Point(   0    , 1.0/3.0 , 0));
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

		points.push_back(Point(  -wallHalfWidth    , -distFromCenter                          ,   0));
		points.push_back(Point(  -sidewalkHalfWidth, -distFromCenter - Building::sidewalkWidth,   0));
		points.push_back(Point(   sidewalkHalfWidth, -distFromCenter - Building::sidewalkWidth,   0));
		points.push_back(Point(   wallHalfWidth    , -distFromCenter                          ,   0));
		points.push_back(Point(  -wallHalfWidth    , -distFromCenter                          ,   0));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	Polygon3d sidewalkTop(model[model.size()-1]);

	for(int x=1; x<8; x++){
		rot.z = 45*x;
		sidewalkTop.setRotation(rot);
		sidewalkTop.setColor(255,255/7*x,255/7*(8-x));
		model.push_back( sidewalkTop.getWorldPoints() );
	}
}