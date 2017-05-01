#include "ai.h"

AI_Tank::AI_Tank(Tank *tank, Tank *enemy){
	
	dx = {1, 0, -1, 0};
        dy = {0, 1, 0, -1};

	n = 360; 
	m = 360; 

	dir = 4;

	this->tank = tank;

	destination = enemy->center;

	start = this->tank->center;

	//std::cout << "start.x " << start.x << " start.y " << start.y << std::endl;
	
	this->fillMap();

	maxTankDist = 15;
	
	dirPrev = 3;
	this->calculatePath();
}

std::string AI_Tank::findPath(const int & xStart, const int &yStart, const int &xEnd, const int &yEnd){

	//std::cout << "findPath " << std::endl;
	
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
				//std::cout << "pth " << path << std::endl;
				x+=dx[j];
				y+=dy[j];
			}
			//std::cout << " about to delete node " << std::endl;
			delete n0;
			//std::cout << "node deleted " << std::endl;
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
		//std::cout << "about to delete node " << std::endl;
		delete n0;
		//std::cout << "node deleted " << std::endl;
	}
	return "";
}


void AI_Tank::fillMap(){


	//std::cout << "fillMap" << std::endl;

	// create empty map
    for(int y=0;y<m;y++)
    {
        for(int x=0;x<n;x++) mapGrid[x][y]=1;
    }

   
        int blocksWide = 2;
        int dist = 60;
        int maxBuildingWidth = 40;
        int streetWidth = 20;
        
	// add path for ai
        for(int x = 0; x < m; x++){
                for( int y = 0; y < n; y++){
                        if(x%((int)(dist/2.0)) == 0 ) 
                                mapGrid[x][y] = 0;
                }
        }


        for(int x = 0; x < m; x++){
                for( int y = 0; y < n; y++){
                        if(y%((int)(dist/2.0)) == 0 )
                                mapGrid[x][y] = 0;
                }

        }

    // set start and target location
    int xA, yA, xB, yB;
    xA = start.x, yA = start.y, xB = destination.x, yB = destination.y;
    //std::cout << "start.x " << start.x << " start.y " << start.y << std::endl;
        mapGrid[xA][yA] = 2;
        mapGrid[xB][yB] = 4;
/*
    for(int y=0;y<m;y++)
        {
            for(int x=0;x<n;x++)
                if(mapGrid[x][y]==0)
                    std::cout<<".";
                else if(mapGrid[x][y]==1)
                    std::cout<<"O";
                else if(mapGrid[x][y]==2)
                    std::cout<<"S";
                else if(mapGrid[x][y]==3)
                    std::cout<<"R";
                else if(mapGrid[x][y]==4)
                    std::cout<<"F";
            std::cout<<std::endl;
        }


    std::cout<<"Map Size (X,Y): "<<n<<","<<m<<std::endl;
    std::cout<<"Start: "<<xA<<","<<yA<<std::endl;
    std::cout<<"Finish: "<<xB<<","<<yB<<std::endl;
*/
}


//forwards
void AI_Tank::forwards(){

	//std::cout << "forwards" << std::endl;

	this->tank->tankSpeed = 0.15;
}
void AI_Tank::forwards(double speed){
	this->tank->tankSpeed = speed;
}
//stop or do nothing
void AI_Tank::stop(){

	//std::cout << "stop" << std::endl;

	this->tank->tankSpeed = 0;
}
//turn left
//turn right
bool AI_Tank::turn(double direction){//assume no angle larger than 360 degrees is passed

	//std::cout << "forwards" << std::endl;

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


void AI_Tank::setRoute(){

	//std::cout << "setRoute " << std::endl;
	
	clock_t startTime = clock();
	std::string routeNew = findPath( start.x, start.y, destination.x, destination.y);//0, 0); //start.x, start.y, destination.x, destination.y);
	//std::cout << "start.x " << start.x << " start.y " << start.y << std::endl;
	//if(routeNew=="") std::cout<<"An empty route generated!"<<std::endl;
    	clock_t endTime = clock();
    	double time_elapsed = double(endTime - startTime);
    	//std::cout<<"Time to calculate the route (ms): "<<time_elapsed<<std::endl;
    	//std::cout<<"Route:"<<std::endl;
    	//std::cout<<routeNew<<std::endl<<std::endl;
	
	route = routeNew;
}

void AI_Tank::followRoute(){

	// updates tank location 


	//std::cout << "followRoute " << std::endl;

	if(route.length()>0){
		int j;
		char c;
		int x = this->tank->center.x;
		int y = this->tank->center.y;

		
		mapGrid[x][y] = 2;
		
		//for(int i = 0; i < route.length(); i++){
		c = route.at(0);
		//std::cout << "c: " << c << std::endl;
		j = atoi(&c);

		if(dirPrev != j){
			int diff = dirPrev - j;
				std::cout << "diff " << diff << std::endl;
			if(diff > 0 && diff%2 == 1){
				turn(270.0);
				std::cout << "turn(270) " << std::endl;
			}
			else if(diff < 0 && diff%2 == 1){
				std::cout << "turn(90) " << std::endl;
				turn(90.0);
			
			}
			else if(diff%2 == 0){
				std::cout << "turn(180) " << std::endl;
				turn(180.0);
			}
		}


		//std::cout << "x=x+dx[j] : " << x=x+dx[j] << " = " << x << " + " << dx[j] << std::endl;
		//std::cout << "y=x+dx[j] : " << y=y+dy[j] << " = " << y << " + " << dy[j] << std::endl;

                //std::cout << y=y+dy[j];


		x=x+dx[j];
		y=y+dy[j];

		//std::cout << x << std::endl;
                //std::cout << y << std::endl;
	
		mapGrid[x][y] = 3;
		
		//std::cout << "this->tank->center.x: " << this->tank->center.x << std::endl;
		//route.erase(0, 1);

		//std::cout << "(x+dx[j]): " << x << std::endl;
		//std::cout << "(y+dy[j]): " << y << std::endl;
			// move tank to next point
		if( this->tank->center.x < (x+dx[j]) && this->tank->center.x > (x-dx[j]) ){
			this->tank->center.x = x+dx[j] * 0.5;		
			//std::cout << "this->tank->center.x" << this->tank->center.x << std::endl;
		}
		/*else if(this->tank->center.x > (x+dx[j]) && dx[j] < 0 ){
                        this->tank->center.x = x+dx[j];                 
                        std::cout << "this->tank->center.x" << this->tank->center.x << std::endl;
                }*/
		else if(this->tank->center.y < (y+dy[j]) && this->tank->center.y > (y-dy[j])){
                        this->tank->center.y = y+dy[j] * 0.5;                 
                        //std::cout << "this->tank->center.y" << this->tank->center.y << std::endl;
                }
		/*else if(this->tank->center.y > (y+dy[j]) && dy[j] < 0 ){
			this->tank->center.y = y+dy[j]; //*0.95; //this->tank->tankSpeed;				
			std::cout << "this->tank->center.y" << this->tank->center.y << std::endl;

		}*/


		else{
			this->tank->center.x = x;  //x+dx[j]; // * 0.5;           
                        //std::cout << "this->tank->center.x" << this->tank->center.x << std::endl;
	
			this->tank->center.y = y; //y+dy[j]; // * 0.5;                 
                        //std::cout << "this->tank->center.y" << this->tank->center.y << std::endl;


			//mapGrid[x][y] = 3;
		}
			//mapGrid[x][y] = 4;
			//update route str
			dirPrev = j;
			route.erase(0, 1);
		//}
	}

}


void AI_Tank::calculatePath(){//int x, int y){//create a new path to new grid coordinate

	//std::cout << "calculatePath " << std::endl;

	//this->destination = Point(0, 0, 0);//60, 60, 0); //Point(x,y,0);
	
	this->setRoute();
	// printf("\ndestination: %f, %f, %f",this->destination.x,this->destination.y,this->destination.z);
	forwards();
}



//AI update function that checks the grid location now, and then gives directions at junctions

void AI_Tank::update_AI(){

	//std::cout << "updateAI " << std::endl;	
	//std::cout << "route " << route << std::endl;	

	if(route.length() > maxTankDist){
		followRoute();
	}
	else{

		//mapGrid[x][y] = 4;
/*
		for(int y=0;y<m;y++){
                                for(int x=0;x<n;x++)
                                        if(mapGrid[x][y]==0)
                                                std::cout<<".";
                                        else if(mapGrid[x][y]==1)
                                                std::cout<<"O"; //obstacle
                                        else if(mapGrid[x][y]==2)
                                                std::cout<<"S"; //start
                                        else if(mapGrid[x][y]==3)
                                                std::cout<<"R"; //route
                                        else if(mapGrid[x][y]==4)
                                                std::cout<<"F"; //finish
                                std::cout<<std::endl;
                        }
*/
		aim(destination);		
	}

}

void AI_Tank::updateTank(Tank *enemy){

	//std::cout << "updateTank " << std::endl;
	
	if(destination != enemy->center){
		destination = enemy->center;
		this->calculatePath();		
	} 
	update_AI();


}

//find the building that is closes to the AI tank that the AI tank wants to look through
void AI_Tank::findNearestBuilding(Point center){
	double x = (Building::maxBuildingWidth/2.0 + center.x) / Building::maxBuildingWidth;//which row
	double y = (Building::maxBuildingWidth/2.0 + center.y) / Building::maxBuildingWidth;//which column
	
}

void AI_Tank::nearbyTarget(Tank * enemy){//check where the enemy tank is, if we think we can aim at him, do so
	if(enemy->center.x - this->tank->center.x < Building::streetWidth/2.0 &&//if its inside a street width we can shoot down the street
		enemy->center.x - this->tank->center.x > -1.0*Building::streetWidth/2.0 ){
		
		aim(enemy->center);
	}
	else if(enemy->center.y - this->tank->center.y < Building::streetWidth/2.0 &&//if its inside a street width we can shoot down the street
		enemy->center.y - this->tank->center.y > -1.0*Building::streetWidth/2.0 ){
		
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
	
	if(delta < 1.0 && delta > -1.0){//if its within one degree, shoot! (Inaccurate at long ranges maybe, but that's ok)
		this->tank->shoot();//spawn a projectile in the global projectiles vector
	}
	this->tank->towerAngle += -3.0*sin(delta *M_PI/180.0);	
}
