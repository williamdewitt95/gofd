
#include "ai.h"




AI_Tank::AI_Tank(Tank *tank){
	this->tank = tank;

	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			grid[i][j] = 1;
		}
	}
	initializeLookupTable();
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
	if ((this->tank->towerAngle > 360) || (this->tank->towerAngle < -360))
		this->tank->towerAngle = 0;

	if(this->tank->cooldown > 0)
		this->tank->cooldown--;

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
	aim(enemy->center);
	// if(enemy->center.x - this->tank->center.x < Building::streetWidth/2.0 &&//if its inside a street width we can shoot down the street
	// 	enemy->center.x - this->tank->center.x > -1.0*Building::streetWidth/2.0 ){
	// 	//TO-DO
	// 	//Detect if there is a building in the way of looking at the player tank
	// 	//
	// 	aim(enemy->center);
	// }
	// else if(enemy->center.y - this->tank->center.y < Building::streetWidth/2.0 &&//if its inside a street width we can shoot down the street
	// 	enemy->center.y - this->tank->center.y > -1.0*Building::streetWidth/2.0 ){
	// 	//TO-DO
	// 	//Detect if there is a building in the way of looking at the player tank
	// 	//
	// 	aim(enemy->center);
	// }
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
	int dist = (int)sqrt(y*y + x*x);
	float vang = lookup(dist);
	float deltaV = this->tank->cannonAngle - vang;
	double delta = this->tank->towerAngle - angle;

	if(deltaV < 1.0 && deltaV > -1.0){
		// printf("delta %f, angle %f, this->tank->towerAngle %f\n",delta,angle, this->tank->towerAngle);

		// printf("\nx %f, angle %f, delta %f\n",x,angle,delta);
		if((delta < 1.0 && delta > -1.0) || (delta < -359.0 && delta > -361.0)){//if its within one degree, shoot! (Inaccurate at long ranges maybe, but that's ok)
			if(dist<255)
				this->tank->shoot();//spawn a projectile in the global projectiles vector
			// printf("\n\nBang!\t %f",this->tank->towerAngle);
		}
		
	}
	this->tank->cannonAngle += -3.0*sin(deltaV *M_PI/180.0);
	
	this->tank->towerAngle += -3.0*sin(delta *M_PI/180.0);

	// printf("deltaV: %f\tthis->cannonAngle = %f\n",deltaV,this->tank->cannonAngle);


}
float AI_Tank::lookup(int distance){
	// printf("   lookup: %d\t",distance);
	if(distance < 213 && distance > 44)
		return this->lookupTable[distance-44];
	else if(distance >=213)
		return 44.5;
	else
		return 3.0;
}

void AI_Tank::initializeLookupTable(){
// angle 	 Distance
// this->lookupTable[168];
	this->lookupTable[	0	] = 	3.2	;
	this->lookupTable[	1	] = 	3.3	;
	this->lookupTable[	2	] = 	3.4	;
	this->lookupTable[	3	] = 	3.5	;
	this->lookupTable[	4	] = 	3.6	;
	this->lookupTable[	5	] = 	3.8	;
	this->lookupTable[	6	] = 	4.1	;
	this->lookupTable[	7	] = 	4.2	;
	this->lookupTable[	8	] = 	4.3	;
	this->lookupTable[	9	] = 	4.4	;
	this->lookupTable[	10	] = 	4.6	;
	this->lookupTable[	11	] = 	4.8	;
	this->lookupTable[	12	] = 	4.9	;
	this->lookupTable[	13	] = 	5.1	;
	this->lookupTable[	14	] = 	5.2	;
	this->lookupTable[	15	] = 	5.3	;
	this->lookupTable[	16	] = 	5.5	;
	this->lookupTable[	17	] = 	5.6	;
	this->lookupTable[	18	] = 	5.7	;
	this->lookupTable[	19	] = 	5.9	;
	this->lookupTable[	20	] = 	6	;
	this->lookupTable[	21	] = 	6.2	;
	this->lookupTable[	22	] = 	6.3	;
	this->lookupTable[	23	] = 	6.4	;
	this->lookupTable[	24	] = 	6.7	;
	this->lookupTable[	25	] = 	6.8	;
	this->lookupTable[	26	] = 	6.9	;
	this->lookupTable[	27	] = 	7	;
	this->lookupTable[	28	] = 	7.3	;
	this->lookupTable[	29	] = 	7.4	;
	this->lookupTable[	30	] = 	7.5	;
	this->lookupTable[	31	] = 	7.7	;
	this->lookupTable[	32	] = 	7.8	;
	this->lookupTable[	33	] = 	8	;
	this->lookupTable[	34	] = 	8.1	;
	this->lookupTable[	35	] = 	8.3	;
	this->lookupTable[	36	] = 	8.4	;
	this->lookupTable[	37	] = 	8.5	;
	this->lookupTable[	38	] = 	8.7	;
	this->lookupTable[	39	] = 	8.9	;
	this->lookupTable[	40	] = 	9	;
	this->lookupTable[	41	] = 	9.1	;
	this->lookupTable[	42	] = 	9.2	;
	this->lookupTable[	43	] = 	9.4	;
	this->lookupTable[	44	] = 	9.6	;
	this->lookupTable[	45	] = 	9.7	;
	this->lookupTable[	46	] = 	9.9	;
	this->lookupTable[	47	] = 	10.1	;
	this->lookupTable[	48	] = 	10.2	;
	this->lookupTable[	49	] = 	10.3	;
	this->lookupTable[	50	] = 	10.4	;
	this->lookupTable[	51	] = 	10.5	;
	this->lookupTable[	52	] = 	10.7	;
	this->lookupTable[	53	] = 	10.9	;
	this->lookupTable[	54	] = 	11	;
	this->lookupTable[	55	] = 	11.3	;
	this->lookupTable[	56	] = 	11.4	;
	this->lookupTable[	57	] = 	11.5	;
	this->lookupTable[	58	] = 	11.7	;
	this->lookupTable[	59	] = 	11.8	;
	this->lookupTable[	60	] = 	12	;
	this->lookupTable[	61	] = 	12.1	;
	this->lookupTable[	62	] = 	12.3	;
	this->lookupTable[	63	] = 	12.4	;
	this->lookupTable[	64	] = 	12.5	;
	this->lookupTable[	65	] = 	12.7	;
	this->lookupTable[	66	] = 	12.8	;
	this->lookupTable[	67	] = 	13.1	;
	this->lookupTable[	68	] = 	13.2	;
	this->lookupTable[	69	] = 	13.4	;
	this->lookupTable[	70	] = 	13.5	;
	this->lookupTable[	71	] = 	13.7	;
	this->lookupTable[	72	] = 	13.8	;
	this->lookupTable[	73	] = 	14	;
	this->lookupTable[	74	] = 	14.2	;
	this->lookupTable[	75	] = 	14.3	;
	this->lookupTable[	76	] = 	14.5	;
	this->lookupTable[	77	] = 	14.7	;
	this->lookupTable[	78	] = 	14.8	;
	this->lookupTable[	79	] = 	15	;
	this->lookupTable[	80	] = 	15.2	;
	this->lookupTable[	81	] = 	15.3	;
	this->lookupTable[	82	] = 	15.4	;
	this->lookupTable[	83	] = 	15.6	;
	this->lookupTable[	84	] = 	15.8	;
	this->lookupTable[	85	] = 	15.9	;
	this->lookupTable[	86	] = 	16.2	;
	this->lookupTable[	87	] = 	16.3	;
	this->lookupTable[	88	] = 	16.4	;
	this->lookupTable[	89	] = 	16.5	;
	this->lookupTable[	90	] = 	16.8	;
	this->lookupTable[	91	] = 	17	;
	this->lookupTable[	92	] = 	17.2	;
	this->lookupTable[	93	] = 	17.4	;
	this->lookupTable[	94	] = 	17.6	;
	this->lookupTable[	95	] = 	17.8	;
	this->lookupTable[	96	] = 	17.9	;
	this->lookupTable[	97	] = 	18	;
	this->lookupTable[	98	] = 	18.2	;
	this->lookupTable[	99	] = 	18.4	;
	this->lookupTable[	100	] = 	18.6	;
	this->lookupTable[	101	] = 	18.8	;
	this->lookupTable[	102	] = 	19.1	;
	this->lookupTable[	103	] = 	19.2	;
	this->lookupTable[	104	] = 	19.5	;
	this->lookupTable[	105	] = 	19.6	;
	this->lookupTable[	106	] = 	19.8	;
	this->lookupTable[	107	] = 	19.9	;
	this->lookupTable[	108	] = 	20.3	;
	this->lookupTable[	109	] = 	20.4	;
	this->lookupTable[	110	] = 	20.6	;
	this->lookupTable[	111	] = 	20.7	;
	this->lookupTable[	112	] = 	21	;
	this->lookupTable[	113	] = 	21.1	;
	this->lookupTable[	114	] = 	21.4	;
	this->lookupTable[	115	] = 	21.5	;
	this->lookupTable[	116	] = 	21.9	;
	this->lookupTable[	117	] = 	22	;
	this->lookupTable[	118	] = 	22.3	;
	this->lookupTable[	119	] = 	22.4	;
	this->lookupTable[	120	] = 	22.6	;
	this->lookupTable[	121	] = 	22.8	;
	this->lookupTable[	122	] = 	22.9	;
	this->lookupTable[	123	] = 	23.3	;
	this->lookupTable[	124	] = 	23.4	;
	this->lookupTable[	125	] = 	23.8	;
	this->lookupTable[	126	] = 	23.9	;
	this->lookupTable[	127	] = 	24.2	;
	this->lookupTable[	128	] = 	24.3	;
	this->lookupTable[	129	] = 	24.7	;
	this->lookupTable[	130	] = 	24.8	;
	this->lookupTable[	131	] = 	25	;
	this->lookupTable[	132	] = 	25.2	;
	this->lookupTable[	133	] = 	25.8	;
	this->lookupTable[	134	] = 	25.9	;
	this->lookupTable[	135	] = 	26.3	;
	this->lookupTable[	136	] = 	26.4	;
	this->lookupTable[	137	] = 	26.7	;
	this->lookupTable[	138	] = 	26.8	;
	this->lookupTable[	139	] = 	27.4	;
	this->lookupTable[	140	] = 	27.5	;
	this->lookupTable[	141	] = 	27.9	;
	this->lookupTable[	142	] = 	28	;
	this->lookupTable[	143	] = 	28.5	;
	this->lookupTable[	144	] = 	28.6	;
	this->lookupTable[	145	] = 	29.1	;
	this->lookupTable[	146	] = 	29.2	;
	this->lookupTable[	147	] = 	29.7	;
	this->lookupTable[	148	] = 	29.8	;
	this->lookupTable[	149	] = 	30.3	;
	this->lookupTable[	150	] = 	30.4	;
	this->lookupTable[	151	] = 	31	;
	this->lookupTable[	152	] = 	31.1	;
	this->lookupTable[	153	] = 	31.9	;
	this->lookupTable[	154	] = 	32	;
	this->lookupTable[	155	] = 	32.6	;
	this->lookupTable[	156	] = 	32.7	;
	this->lookupTable[	157	] = 	33.5	;
	this->lookupTable[	158	] = 	33.6	;
	this->lookupTable[	159	] = 	34.6	;
	this->lookupTable[	160	] = 	34.7	;
	this->lookupTable[	161	] = 	35.6	;
	this->lookupTable[	162	] = 	36.1	;
	this->lookupTable[	163	] = 	36.2	;
	this->lookupTable[	164	] = 	37.7	;
	this->lookupTable[	165	] = 	37.8	;
	this->lookupTable[	166	] = 	39.3	;
	this->lookupTable[	167	] = 	40	;
	this->lookupTable[	168	] = 	44.5	;
}