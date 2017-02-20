
#include "ai.h"




AI_Tank::AI_Tank(Tank *tank){
	this->tank = tank;

	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			grid[i][j] = 1;
		}
	}
	// calculatePath(this->tank->center.x, this->tank->center.y);//stay still -- DEBUG
	calculatePath(Building::distanceBetweenBuildings*(rand()%NUM_BLOCKS_WIDE)+Building::streetWidth/2.0 + Building::maxBuildingWidth/2.0,//randomly generate a point to go to
				  Building::distanceBetweenBuildings*(rand()%NUM_BLOCKS_WIDE)+Building::streetWidth/2.0 + Building::maxBuildingWidth/2.0);
}



//something to hold the grid in - 2d array? - Do we even need a grid? Might be able to just calculate based positions of buildings (since we know them)



//forwards
void AI_Tank::forwards(){
	this->tank->tankSpeed = 0.15;
}
void AI_Tank::forwards(double speed){
	this->tank->tankSpeed = speed;
}
//stop or do nothing
void AI_Tank::stop(){
	this->tank->tankSpeed = 0;
}
//turn left
//turn right
bool AI_Tank::turn(double direction){//assume no angle larger than 360 degrees is passed
	if(direction < 0){
		direction += 360.0;
	}
	float turn = direction - this->tank->baseAngle ;//tank->baseAngle can never be above 360
	if(this->tank->baseAngle < 0)
		turn += 360.0;
	else if(this->tank->baseAngle > 360.0)
		turn -= 360.0;
	

	if(turn < 1.0 && turn > -1.0){
		// printf("Forwards");
		forwards();
	}
	else if(turn > 0.0){
		stop();
		this->tank->baseAngle++;
	}
	else{
		stop();
		this->tank->baseAngle--;
	}
	
	return false;
}



void AI_Tank::calculatePath(int x, int y){//create a new path to new grid coordinate
	this->destination = Point(x,y,0);
	// printf("\ndestination: %f, %f, %f",this->destination.x,this->destination.y,this->destination.z);
	forwards();
}



//AI update function that checks the grid location now, and then gives directions at junctions

void AI_Tank::update_AI(){
	if((int)this->tank->center.x > (int)this->destination.x){//for now, we will simply go down x until we reach destination x, then we go down y
		turn(90.0);
	}
	else if((int)this->tank->center.x < (int)this->destination.x){
		turn(270.0);
	}
	else if((int)this->tank->center.y > (int)this->destination.y){
		turn(180.0);
	}
	else if((int)this->tank->center.y < (int)this->destination.y){
		turn(0.0);
	}
	else{//at location
		calculatePath(Building::distanceBetweenBuildings*(rand()%NUM_BLOCKS_WIDE)+Building::streetWidth/2.0 + Building::maxBuildingWidth/2.0,
				  Building::distanceBetweenBuildings*(rand()%NUM_BLOCKS_WIDE)+Building::streetWidth/2.0 + Building::maxBuildingWidth/2.0);
		stop();
	}

}

void AI_Tank::updateTank(){
	update_AI();
	this->tank->center.x += this->tank->tankSpeed * cos((this->tank->baseAngle + 90) * (M_PI / 180));
	this->tank->center.y += this->tank->tankSpeed * sin((this->tank->baseAngle + 90) * (M_PI / 180));
	if ((this->tank->baseAngle > 360) || (this->tank->baseAngle < -360))
		this->tank->baseAngle = 0;
	// this->baseAngle += tankBaseRotate;
	// this->towerAngle += tankTurretRotate;
	// this->cannonAngle += tankCannonRotate;

}

//find the building that is closes to the AI tank that the AI tank wants to look through
void AI_Tank::findNearestBuilding(Point center){
	double x = (Building::maxBuildingWidth/2.0 + center.x) / Building::maxBuildingWidth;//which row
	double y = (Building::maxBuildingWidth/2.0 + center.y) / Building::maxBuildingWidth;//which column
	//NUM_BLOCKS_WIDE*x + y//vectors stored linearly in memory, so go the number of columns + the number of rows
	// if(this->)
}

void AI_Tank::nearbyTarget(Tank * enemy){//check where the enemy tank is, if we think we can aim at him, do so
	if(enemy->center.x - this->tank->center.x < Building::streetWidth/2.0 &&//if its inside a street width we can shoot down the street
		enemy->center.x - this->tank->center.x > -1.0*Building::streetWidth/2.0 ){
		//TO-DO
		//Detect if there is a building in the way of looking at the player tank
		//
		aim(enemy->center);
	}
	else if(enemy->center.y - this->tank->center.y < Building::streetWidth/2.0 &&//if its inside a street width we can shoot down the street
		enemy->center.y - this->tank->center.y > -1.0*Building::streetWidth/2.0 ){
		//TO-DO
		//Detect if there is a building in the way of looking at the player tank
		//
		aim(enemy->center);
	}
}


void AI_Tank::aim(Point enemy){
	double y = this->tank->center.y - enemy.y;
	double x = this->tank->center.x - enemy.x;
	double angle = (180.0/M_PI * atan(y / x) + 90.0);
	if(x < 0.0){
		angle += 180.0;
	}
	else{
		//do nothing
	}
	double delta = this->tank->towerAngle - angle;
	// printf("\nx %f, angle %f, delta %f\n",x,angle,delta);
	if(delta < 1.0 && delta > -1.0){//if its within one degree, shoot! (Inaccurate at long ranges maybe, but that's ok)
		projectiles.push_back(this->tank->shoot());//spawn a projectile in the global projectiles vector
		// printf("\n\nBang!\t %f",this->tank->towerAngle);
	}
	this->tank->towerAngle += -3.0*sin(delta *M_PI/180.0);
	
}