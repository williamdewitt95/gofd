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
//c is the center point of sphere, n is normal of plane, p is point on plane
bool sphereToPlane(Point c, double radius,Vector n, Point p){
	double dist = ((c.x-p.x)*n.x + (c.y-p.y)*n.y + (c.z-p.z)*n.z)	/ sqrt(n.x^2 + n.y^2 + n.z^2);
	if (dist>radius) return 0;
	else return 1;
}

/*

void collisionDetect(Tank*& tank, std::vector<Building*>& buildings, std::vector<Target*>& targets, std::vector<Projectile*> projectile){

	double targetRadius;
	double tankRadius = distance(tank->getFurthestPoint(), tank->center);
	double tankProjCenterDistance;
	double projTankCenterDistance; 
	double projRadius;
	double tarRadius;

	// getFurthestPoint (alternately radius variable) should return point of each object furthest from center  

	// check tank & building collision
	// projectile collision
	
	\*
 	*
 	*
 	* cases: 
 	*
 	* 	>1: projectile + building
 	* 	>2: projectile + targets
 	* 	>3: tank + building
 	* 	>4: tank + projectile
 	*
 	*
 	*\

	// cases 1 and 2
		
	for (int i = 0; i < projectiles.size(); i++){
		
		// case 4
		projTankCenterDistance = distance(tank->center(), projectiles[i]->center());	
		projectileRadius = distance(projectiles[i]-> getFurthestPoint(), targets[i]->center());		

		if(! (tankRadius+projectileRadius < projTankCenterDistance) ){
			// set tank collision flag to true
			tank->collision = true;
			projectile->collision = true;
		}

		// case 2
		for (int j = 0; j < targets.size(); j++){

			tarProjCenterDistance = distance(projectiles[i]->center(), targets[j]->center);
			tarRadius = distance(projectiles[i]->getFurthestPoint(), targets[j]->getFurthestPoint());
			
			if(!(projectileRadius+tarRadius < tarProjCenterDistance)){
				projectiles[i]->collision = true;
				targets[j]->collision = true;
			}


		}
				


		else
			tank->collision = false;

	}
		

}
*/
