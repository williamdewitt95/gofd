
#include "ai.h"
//#include "mapnode.h"

AI_Tank::AI_Tank(Tank *tank){

	//std::cout << "tank constructor" << std::endl;

	//numDir = 8;

	dx = {1, 1, 0, -1, -1, 0, 1};
        dy = {0, 1, 1, 1, 0, -1, -1, -1};

	n = 100;
	m = 100;

	dir = 8;

	//numDir = 8;

	this->tank = tank;

	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			grid[i][j] = 1;
		}
	}
	
	calculatePath(Building::distanceBetweenBuildings*(rand()%NUM_BLOCKS_WIDE)+Building::streetWidth/2.0 + Building::maxBuildingWidth/2.0,//randomly generate a point to go to
				  Building::distanceBetweenBuildings*(rand()%NUM_BLOCKS_WIDE)+Building::streetWidth/2.0 + Building::maxBuildingWidth/2.0);

}



//something to hold the grid in - 2d array? - Do we even need a grid? Might be able to just calculate based positions of buildings (since we know them)
/*
bool AI_Tank::operator<(const MapNode& a, const MapNode& b) const{
	return a.getPriority() > b.getPriority();
}
*/

// a star algorithm implementation
// returns route in string of digits


std::string AI_Tank::findPath(const int & xStart, const int &yStart, const int &xEnd, const int &yEnd){
	
	static std::priority_queue<MapNode> pq[2];
	static int pqi;
	static MapNode* n0;
	static MapNode* m0;
	static int i, j, x, y, xdx, ydy;
	static char c;
	pqi=0;

	for(y=0; y<m; y++){
		for(x=0; x<n; x++){
			checkedMap[x][y]=0;
			uncheckedMap[x][y]=0;
		}
	}

	n0 = new MapNode(xStart, yStart , 0, 0);
	n0->priorityUpdate(xEnd, yEnd);
	pq[pqi].push(*n0);
	uncheckedMap[x][y]=n0->getPriority();

	while(!pq[pqi].empty()){
		n0=new MapNode(pq[pqi].top().getXPos(), pq[pqi].top().getYPos(), pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

		x=n0->getXPos(); y=n0->getYPos();

		pq[pqi].pop();
		uncheckedMap[x][y]=0;
		checkedMap[x][y]=1;

		if(x==xEnd && y==yEnd){
			std::string path="";
			while(!(x==xStart && y==yStart)){
				j=directionalMap[x][y];
				c='0'+(j+dir/2)%dir;
				path=c+path;
				x+=dx[j];
				y+=dy[j];
			}

			delete n0;
			while(!pq[pqi].empty())
				pq[pqi].pop();

			return path;
		}

		for(i=0; i < dir; i++){
			xdx=x+dx[i]; ydy = y + dy[i];

			if(!(xdx<0 || xdx>n-1 || ydy<0 || ydy>m-1 || mapGrid[xdx][ydy]==1|| checkedMap[xdx][ydy]==1)){
	
				m0=new MapNode(xdx, ydy, n0->getLevel(), n0->getPriority());
				m0->incLevel(i);
				m0->priorityUpdate(xEnd, yEnd);
				
				if(uncheckedMap[xdx][ydy]==0){
					uncheckedMap[xdx][ydy]=m0->getPriority();
					pq[pqi].push(*m0);

					directionalMap[xdx][ydy]=(i+dir/2)%dir;
				}
				else if(uncheckedMap[xdx][ydy]>m0->getPriority()){
					uncheckedMap[xdx][ydy]=m0->getPriority();
					directionalMap[xdx][ydy]=(i+dir/2)%dir;

					while(!(pq[pqi].top().getXPos() == xdx && pq[pqi].top().getYPos()==ydy)){
						pq[1-pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop();

					if(pq[pqi].size()>pq[1-pqi].size())
						pqi = 1 - pqi;
					while(!pq[pqi].empty()){
						pq[1-pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}

					pqi = 1 - pqi;
					pq[pqi].push(*m0);
				}
				else delete m0;
			}
		}
		delete n0;
	}
	return "";
}


void AI_Tank::forwards(){

	//std::cout << "tank forwards" << std::endl;

	this->tank->tankSpeed = 0.15;
}
void AI_Tank::forwards(double speed){

	//std::cout << "tank forwards" << std::endl;
	this->tank->tankSpeed = speed;
}
//stop or do nothing
void AI_Tank::stop(){

	//std::cout << "tank stop" << std::endl;
	this->tank->tankSpeed = 0;
}
//turn left
//turn right
bool AI_Tank::turn(double direction){//assume no angle larger than 360 degrees is passed

	//std::cout << "tank turn" << std::endl;
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

	//std::cout << "tank calcPath" << std::endl;
	this->destination = Point(x,y,0);
	// printf("\ndestination: %f, %f, %f",this->destination.x,this->destination.y,this->destination.z);
	forwards();
}



//AI update function that checks the grid location now, and then gives directions at junctions

void AI_Tank::update_AI(){

	//std::cout << "tank update_ai" << std::endl;

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

	//std::cout << "tank update" << std::endl;
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

	//std::cout << "tank find nearest building" << std::endl;
	double x = (Building::maxBuildingWidth/2.0 + center.x) / Building::maxBuildingWidth;//which row
	double y = (Building::maxBuildingWidth/2.0 + center.y) / Building::maxBuildingWidth;//which column
	//NUM_BLOCKS_WIDE*x + y//vectors stored linearly in memory, so go the number of columns + the number of rows
	// if(this->)
}


Target* AI_Tank::setClosestTarget(std::vector<Target*> targets){
	
	//std::cout << "tank setClosestTarget" << targets[0] << std::endl;
	double dist = targets[0]->center.distance(this->tank->center);	
	double tempDist;
	
	Target *closestTarget = targets[0];

	for(int i = 1; i<targets.size(); i++){
		
		tempDist = targets[i]->center.distance( this->tank->center);
		//std::cout << "closest target " << i << "\t" << targets[i]->center.x << "\t" << targets[i]->center.y << std::endl;
	
		if(tempDist < dist){
			closestTarget = targets[i];
			dist = tempDist;

			//std::cout << "closest target " << targets[i] << std::endl;
		}
	}



	return closestTarget;

}


void AI_Tank::nearbyTarget(Target *target){ //Tank * enemy){//check where the enemy tank is, if we think we can aim at him, do so

	//std::cout << "tank nearbyTarget " << target->center.x << "\t" << target->center.y << std::endl;

	if(target->center.x - this->tank->center.x < Building::streetWidth/2.0 &&//if its inside a street width we can shoot down the street
		target->center.x - this->tank->center.x > -1.0*Building::streetWidth/2.0 ){
		//TO-DO
		//Detect if there is a building in the way of looking at the player tank
		//
		aim(target->center);
	}
	else if(target->center.y - this->tank->center.y < Building::streetWidth/2.0 &&//if its inside a street width we can shoot down the street
		target->center.y - this->tank->center.y > -1.0*Building::streetWidth/2.0 ){
		//TO-DO
		//Detect if there is a building in the way of looking at the player tank
		//
		aim(target->center);
	}
}


void AI_Tank::aim(Point target){
	
	//std::cout << "tank aim" << std::endl;

	double y = this->tank->center.y - target.y;
	double x = this->tank->center.x - target.x;
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
		this->tank->shoot();//spawn a projectile in the global projectiles vector
		// printf("\n\nBang!\t %f",this->tank->towerAngle);
	}
	this->tank->towerAngle += -3.0*sin(delta *M_PI/180.0);
	
}
