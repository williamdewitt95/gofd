#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "../polygon3d.h"
#include "../globals.h"
#include "window1.cpp"

using std::vector;

void apartmentHighriseBuilding(vector<Polygon3d> &model, vector<Polygon3d> &boundingBox, vector<unsigned int> &subLists){
	const int minFloors = 6;
	const int maxFloors = 15;
	const double floorHeight = 5;
	const double buildingWidth = Building::maxBuildingWidth;
	const double sidewalkWidth = Building::sidewalkWidth;
	const double streetWidth = Building::streetWidth;
	
	// == main building ==
	int numFloors = (rand() % (maxFloors - minFloors)) + minFloors;
	{
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		loadTex("textures/buildings/brick1.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/buildings/brick1.jpg"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point(  -buildingWidth/2.0, -buildingWidth/2.0,  numFloors*floorHeight));
		points.push_back(Point(  -buildingWidth/2.0, -buildingWidth/2.0,                      0));
		points.push_back(Point(   buildingWidth/2.0, -buildingWidth/2.0,                      0));
		points.push_back(Point(   buildingWidth/2.0, -buildingWidth/2.0,  numFloors*floorHeight));
		points.push_back(Point(  -buildingWidth/2.0, -buildingWidth/2.0,  numFloors*floorHeight));
		texs.push_back(Point(       0                        ,         0, 0));
		texs.push_back(Point(       0                        , numFloors, 0));
		texs.push_back(Point(floor(buildingWidth/floorHeight), numFloors, 0));
		texs.push_back(Point(floor(buildingWidth/floorHeight),         0, 0));
		texs.push_back(Point(       0                        ,         0, 0));
	}
	Polygon3d singleSide(model[model.size()-1]);
	Vector rot(0,0,0);
	for(int x=1; x<4; x++){
		rot.z = 90*x;
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

		points.push_back(Point( -buildingWidth/2.0,  buildingWidth/2.0, numFloors*floorHeight ));
		points.push_back(Point( -buildingWidth/2.0, -buildingWidth/2.0, numFloors*floorHeight ));
		points.push_back(Point(  buildingWidth/2.0, -buildingWidth/2.0, numFloors*floorHeight ));
		points.push_back(Point(  buildingWidth/2.0,  buildingWidth/2.0, numFloors*floorHeight ));
		points.push_back(Point( -buildingWidth/2.0,  buildingWidth/2.0, numFloors*floorHeight ));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}

	boundingBox = model; // copy the simple parts



	// == Windows ==
	// unsigned int windowList; // displaylist to call for drawing the windows
	{
		int numWindowsPerSide = floor(buildingWidth/floorHeight);
		double distBetweenWindows = buildingWidth / numWindowsPerSide;
		double windowHeight = floorHeight * 0.5;
		double windowWidth = distBetweenWindows * 0.35;

		Point gridOffset;

		gridOffset.x = distBetweenWindows / 2.0 - buildingWidth/2.0; // bottom left corner + half the window distance
		gridOffset.y = -1 * buildingWidth/2.0;
		gridOffset.z = floorHeight/2.0;
		for(int y=1; y<numFloors; y++){
			for(int x=0; x<numWindowsPerSide; x++){
				makeNewWindow1(
					Point( distBetweenWindows * x , 0 , floorHeight * y ) + gridOffset, // centerpoint for the window starts at ground floor-left side
					0, // rotation
					windowHeight, // height
					windowWidth,
					model
				);
			}
		}

		gridOffset.x = -1 * buildingWidth/2.0;
		gridOffset.y = distBetweenWindows / 2.0 - buildingWidth/2.0; // bottom left corner + half the window distance
		gridOffset.z = floorHeight/2.0;
		for(int y=1; y<numFloors; y++){
			for(int x=0; x<numWindowsPerSide; x++){
				makeNewWindow1(
					Point( 0 , distBetweenWindows * x , floorHeight * y ) + gridOffset, // centerpoint for the window starts at ground floor-left side
					270, // rotation
					windowHeight, // height
					windowWidth,
					model
				);
			}
		}

		gridOffset.x = buildingWidth/2.0;
		gridOffset.y = distBetweenWindows / 2.0 - buildingWidth/2.0; // bottom left corner + half the window distance
		gridOffset.z = floorHeight/2.0;
		for(int y=1; y<numFloors; y++){
			for(int x=0; x<numWindowsPerSide; x++){
				makeNewWindow1(
					Point( 0 , distBetweenWindows * x , floorHeight * y ) + gridOffset, // centerpoint for the window starts at ground floor-left side
					90, // rotation
					windowHeight, // height
					windowWidth,
					model
				);
			}
		}

		gridOffset.x = distBetweenWindows / 2.0 - buildingWidth/2.0; // bottom left corner + half the window distance
		gridOffset.y = buildingWidth/2.0;
		gridOffset.z = floorHeight/2.0;
		for(int y=1; y<numFloors; y++){
			for(int x=0; x<numWindowsPerSide; x++){
				makeNewWindow1(
					Point( distBetweenWindows * x , 0 , floorHeight * y ) + gridOffset, // centerpoint for the window starts at ground floor-left side
					180, // rotation
					windowHeight, // height
					windowWidth,
					model
				);
			}
		}
	} // windows



	// == Sidewalk ==
	{
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		// loadTex("textures/cloud.png");
		// model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/cloud.png"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point(  -buildingWidth/2.0                , -buildingWidth/2.0                ,   0.15));
		points.push_back(Point(  -buildingWidth/2.0 - sidewalkWidth, -buildingWidth/2.0 - sidewalkWidth,   0.15));
		points.push_back(Point(   buildingWidth/2.0 + sidewalkWidth, -buildingWidth/2.0 - sidewalkWidth,   0.15));
		points.push_back(Point(   buildingWidth/2.0                , -buildingWidth/2.0                ,   0.15));
		points.push_back(Point(  -buildingWidth/2.0                , -buildingWidth/2.0                ,   0.15));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	Polygon3d sidewalkTop(model[model.size()-1]);

	rot.z = 90;
	sidewalkTop.setRotation(rot);
	sidewalkTop.setColor(255,125,125);
	model.push_back( sidewalkTop.getWorldPoints() );

	rot.z = 180;
	sidewalkTop.setRotation(rot);
	sidewalkTop.setColor(125,255,125);
	model.push_back( sidewalkTop.getWorldPoints() );

	rot.z = 270;
	sidewalkTop.setRotation(rot);
	sidewalkTop.setColor(125,125,255);
	model.push_back( sidewalkTop.getWorldPoints() );

	double curbDarkness = 0.85; // how much darker the curb should be to add a little depth to things
	{
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		// loadTex("textures/cloud.png");
		// model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/cloud.png"].textureRef);
		model[model.size()-1].setColor(255*curbDarkness,255*curbDarkness,255*curbDarkness);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point(  -buildingWidth/2.0 - sidewalkWidth, -buildingWidth/2.0 - sidewalkWidth, Building::sidewalkThickness));
		points.push_back(Point(  -buildingWidth/2.0 - sidewalkWidth, -buildingWidth/2.0 - sidewalkWidth,              0             ));
		points.push_back(Point(   buildingWidth/2.0 + sidewalkWidth, -buildingWidth/2.0 - sidewalkWidth,              0             ));
		points.push_back(Point(   buildingWidth/2.0 + sidewalkWidth, -buildingWidth/2.0 - sidewalkWidth, Building::sidewalkThickness));
		points.push_back(Point(  -buildingWidth/2.0 - sidewalkWidth, -buildingWidth/2.0 - sidewalkWidth, Building::sidewalkThickness));
		texs.push_back(Point(0,0,0));
		texs.push_back(Point(0,1,0));
		texs.push_back(Point(1,1,0));
		texs.push_back(Point(1,0,0));
		texs.push_back(Point(0,0,0));
	}
	Polygon3d sidewalkCurb(model[model.size()-1]);

	rot.z = 90;
	sidewalkCurb.setRotation(rot);
	sidewalkCurb.setColor(255*curbDarkness,125*curbDarkness,125*curbDarkness);
	model.push_back( sidewalkCurb.getWorldPoints() );

	rot.z = 180;
	sidewalkCurb.setRotation(rot);
	sidewalkCurb.setColor(125*curbDarkness,255*curbDarkness,125*curbDarkness);
	model.push_back( sidewalkCurb.getWorldPoints() );

	rot.z = 270;
	sidewalkCurb.setRotation(rot);
	sidewalkCurb.setColor(125*curbDarkness,125*curbDarkness,255*curbDarkness);
	model.push_back( sidewalkCurb.getWorldPoints() );
}