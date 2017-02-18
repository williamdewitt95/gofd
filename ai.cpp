
#include "ai.h"


AI_Tank::AI_Tank(Tank *tank){
	this->tank = tank;

	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			grid[i][j] = 1;
		}
	}

	calculatePath(rand()%15,rand()%15);
}


//forwards
void AI_Tank::forwards(){
	this->tank->tankSpeed = 0.05;
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
	// if(turn == 0){
	// 	forwards();
	// 	return true;
	// }
	// else{
	// 	stop();
	// 	this->tank->baseAngle += 1;
	// }
	// else if(turn <180){
	// 	stop();
	// 	this->tank->baseAngle-=.5;
	// }
	// else{
	// 	stop();
	// 	this->tank->baseAngle+=.5;
	// }

	if(turn < 1.0 && turn > -1.0){
		printf("Forwards");
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
	

	printf("\ndir %.1f, base %.2f, curr (%.1f, %.1f), dest (%.1f, %.1f)",direction,this->tank->baseAngle, this->tank->center.x, this->tank->center.y, this->destination.x, this->destination.y);
	printf("\nthis->tank->center.x - this->destination.x %f\n",this->tank->center.x - this->destination.x);
	return false;
}

//something to hold the grid in - 2d array?


void AI_Tank::calculatePath(int x, int y){//create a new path to new grid coordinate
	this->destination = Point(x,y,0);
	printf("\ndestination: %f, %f, %f",this->destination.x,this->destination.y,this->destination.z);
	forwards();
}



//AI update function that checks the grid location now, and then gives directions at junctions

void AI_Tank::update_AI(){
	if((int)this->tank->center.x > (int)this->destination.x){
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
		calculatePath(rand()%15,rand()%15);
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