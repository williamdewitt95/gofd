#include "building.h"
#include "buildings/generic1.cpp"
#include "buildings/genericOctogon.cpp"

const double Building::sidewalkWidth = 3;
const double Building::maxBuildingWidth = 40;
const double Building::distanceBetweenBuildings = 60;
const double Building::streetWidth = 60 - 40; // distanceBetweenBuildings - maxBuildingWidth;

Building::Building(Point center){
	this->center = center;
	this->alreadyCalculated = false;
	const int numOfBuildings = 2;
	switch(rand() % numOfBuildings){
		case 0:
			createGeneric1Building(model,box);
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
}

void Building::draw(){
	glPushMatrix();
	glTranslated(center.x,center.y,center.z);
	for(int x=0; x<model.size(); x++)
		this->model[x].draw();
	glPopMatrix();
}
void Building::update(){
}
std::vector<Polygon3d> Building::boundingBox(){
	//static bool alreadyCalculated = false;
	if(!(this->alreadyCalculated)){
		for(int x=0; x < this->box.size(); x++){
			//printf("Starting to translate bounding box\n");
			this->box[x].setCenter(this->center);
			//printf("About to copy of num points %d\n",this->box[x].numPoints());
			Polygon3d p=this->box[x].getTransform();
			//printf("Made the copy of num points %d\n",p.numPoints());
			this->box[x] = p;
			//printf("put into the array\n");
		}
	}
	this->alreadyCalculated = true;
	return this->box;
}
