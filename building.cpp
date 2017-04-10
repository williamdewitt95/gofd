#include "building.h"
#include "buildings/apartmentHighrise.cpp"
#include "buildings/generic1.cpp"
#include "buildings/genericOctogon.cpp"

const double Building::sidewalkWidth = 3;
const double Building::sidewalkThickness = 0.15;
const double Building::maxBuildingWidth = 40;
const double Building::distanceBetweenBuildings = 60;
const double Building::streetWidth = 60 - 40; // distanceBetweenBuildings - maxBuildingWidth;

Building::Building(Point center){
	this->center = center;
	const int numOfBuildings = 2;
	switch(rand() % numOfBuildings){
		case 0:
			// createGeneric1Building(model,boundingBox);
			apartmentHighriseBuilding(DrawableObject::model,DrawableObject::boundingBox,subLists,sideNorth,sideEast,sideSouth,sideWest);
			break;
		case 1:
			createGenericOctogonBuilding(DrawableObject::model,DrawableObject::boundingBox);
			break;

		// === insert new building before here ===
		default:
			createGeneric1Building(DrawableObject::model,DrawableObject::boundingBox);
			printf("Building selection out of range\n");
			break;
	}
	listName = glGenLists(1);
	glNewList(listName,GL_COMPILE);
	this->draw_CPU();
	glEndList();
}

void Building::draw(){
	int dx = GLOBAL.CAMERA_POS.x - this->center.x;
	int dy = GLOBAL.CAMERA_POS.y - this->center.y;
	if( abs(dx) > 2*distanceBetweenBuildings &&
		abs(dy) > 2*distanceBetweenBuildings )
			return;

	glPushMatrix();
	glTranslated(center.x,center.y,center.z);

	glCallList(listName);

	if(dy>0){
		for(int x=0; x<sideNorth.size(); x++)
			glCallList(sideNorth[x]);
	}else{
		for(int x=0; x<sideSouth.size(); x++)
			glCallList(sideSouth[x]);
	}

	if(dx>0){
		for(int x=0; x<sideEast.size(); x++)
			glCallList(sideEast[x]);
	}else{
		for(int x=0; x<sideWest.size(); x++)
			glCallList(sideWest[x]);
	}

	glPopMatrix();
	// this->draw_CPU();
}
void Building::draw_CPU(){
	for(int x=0; x<model.size(); x++)
		this->model[x].getTransform().draw_static();
	for(int x=0; x<subLists.size(); x++)
		glCallList(subLists[x]);
}
