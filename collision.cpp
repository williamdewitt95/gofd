#include "collision.h"


/*
Distance function usage
	Point *a = new Point(0,0,0);
        Point *b = new Point(0,0,5);
        cout << "distance between a and b: " << distance(*a,*b) << "\n";
	This will print the value 5
*/
//Uses the Point class
double distance(Point a, Point b){

	double xdif, ydif, zdif;

	xdif = a.x - b.x;
	ydif = a.y - b.y;
	zdif = a.x - b.z;

	return sqrt(pow(xdif,2)+pow(ydif,2)+pow(zdif,2));


}

//Uses the Vector class
double distance(Vector a, Vector b){

	double xdif, ydif, zdif;

        xdif = a.x - b.x;
        ydif = a.y - b.y;
        zdif = a.x - b.z;

        return sqrt(pow(xdif,2)+pow(ydif,2)+pow(zdif,2));

}

/*
void collisionDetect(Tank*& tank, std::vector<Building*>& buildings, std::vector<Target*>& targets){

	double targetRadius;
	double tankRadius = distance(tank->getFurthestPoint(), tank->center);
	double centerDistance; 

	// getFurthestPoint method should return point of each object furthest from center  

	for (int i = 0; i < targets.size(); i++){
		
		centerDistance = (tank->getFurthestPoint(), targets[i]->getFurthestPoint();	
		targetRadius = distance(targets[i]-> getFurthestPoint(), targets[i]->center());		

		if(! (tankRadius+targetRadius < centerDistance) ){
			// set tank collision flag to true
			tank->collision = true;
		}
		else
			tank->collision = false;

	}
		

}
*/
