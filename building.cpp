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
			// createGeneric1Building(model,box);
			apartmentHighriseBuilding(model,box,subLists);
			break;
		case 1:
			createGenericOctogonBuilding(model,box);
			break;

		// === insert new building before here ===
		default:
			createGeneric1Building(model,box);
			printf("Building selection out of range\n");
			break;
	}
	listName = glGenLists(1);
	glNewList(listName,GL_COMPILE);
	this->draw_CPU();
	glEndList();
}

void Building::draw(){
	glCallList(listName);
	// this->draw_CPU();
}
void Building::draw_CPU(){
	glPushMatrix();
	glTranslated(center.x,center.y,center.z);
	for(int x=0; x<model.size(); x++)
		this->model[x].draw();
	for(int x=0; x<subLists.size(); x++)
		glCallList(subLists[x]);
	glPopMatrix();
}
void Building::update(){
}
std::vector<Polygon3d> Building::boundingBox(){
	return this->box;
}
