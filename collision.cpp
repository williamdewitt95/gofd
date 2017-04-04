#include "collision.h"
// chris:: Struct introduces the paramaters of a plane
struct plane {
	double a;
	double b;
	double c;
	double d;
};

double distSquare(Point a, Point b){

	double xdif, ydif, zdif;

        xdif = a.x - b.x;
        ydif = a.y - b.y;
        zdif = a.z - b.z;

        return pow(xdif,2)+pow(ydif,2)+pow(zdif,2);

}

double distSquare(Vector a, Vector b){

	double xdif, ydif, zdif;

        xdif = a.x - b.x;
        ydif = a.y - b.y;
        zdif = a.z - b.z;

        return pow(xdif,2)+pow(ydif,2)+pow(zdif,2);

}

/*
Distance function usage
	Point *a = new Point(0,0,0);
        Point *b = new Point(0,0,5);
        cout << "distance between a and b: " << distance(*a,*b) << "\n";
	This will print the value 5
*/
//Uses the Point class
double distance(Point a, Point b){

	return sqrt(distSquare(a,b));

}

//Uses the Vector class
double distance(Vector a, Vector b){

        return sqrt(distSquare(a,b));

}
//c is the center point of sphere, n is normal of plane, p is point on plane
bool sphereToPlane(Point c, double radius,Vector n, Point p){
	//double dist = ((c.x-p.x)*n.x + (c.y-p.y)*n.y + (c.z-p.z)*n.z)	/ sqrt(n.x^2 + n.y^2 + n.z^2);
	//if (dist>radius) return 0;
	//else 
	return 1;
}

bool pointToPolygon(Point p, std::vector<Point> shape){//assumes point is on plane
	double total = 0.0;
	
	for(int i = 0; i < shape.size(); i++){
		Vector v1 = Vector(p,shape[i]);
		if(i == 3){
			Vector v2 = Vector(p,shape[0]);
			total += v1.angleBtw(v2);

		}
		else {
			Vector v2 = Vector(p,shape[i + 1]);
			total += v1.angleBtw(v2);
		}
	}
	if (total == 360) return true;
	else return 0;
}

// chris:: Takes in 4 points.  3 points of which are on the plane
// 4th point not ont he plane.  The three points will be converted
// to parameters of a plane and then the equation for the plane
// will be taken and the distance between point 4 and a orthogonal point
// is calculated
// For chris:: Currently doesn't calculate the distance corect
// division sign? 
double distPlaneToPoint (Point a, Point b, Point c, Point d)
{
	plane tmp;
	Vector v1, v2, v3;
	v1 = Vector (a,b);
	v2 = Vector (a,c);
	v3 = v1.cross (v2);
	tmp.a = v3.x; tmp.b = v3.y; tmp.c = v3.z;
	tmp.d = -1*v3.x*a.x + -1*v3.y*a.y + -1*v3.z*a.z;
	return abs(tmp.a*d.x + tmp.b*d.y + tmp.c*d.z + tmp.d)/(sqrt(tmp.a*tmp.a + tmp.b*tmp.b + tmp.c*tmp.c));
}


bool collisionDetect(Point center, double sphdist, std::vector<Building*>& buildings, std::vector<Target*>& targets, std::vector<Projectile*>& projectiles){

	Point a = Point(12,16,45);
	Point b = Point(12,12,45);
        Point c = Point(16,12,45);
        Point d = Point(32,64,0);
	printf("test distplanetopoint: %f\n", distPlaneToPoint(a,b,c,d));

	for(int i = 0; i < buildings.size(); i++){

                //tbDist has the distance between the center point and the buildings center
                double tbDist = distance(center,buildings[i]->center);
		//printf("About to copy\n");
		std::vector<Polygon3d> sides = buildings[i]->boundingBox();
		//printf("%f\n",tbDist);
                if(tbDist < sphdist + buildings[i]->maxBuildingWidth/2+5){
                        
			//printf("before here\n");
			for(int j = 0; j < sides.size(); j++){
			//for(int j = 0; j < 3; j++){
				//printf("Here\n");
				Polygon3d wall = sides[j];
				std::vector<Point> worldCoords = wall.getPoints();

				for(int k =0; k < 3 ; k++){
					printf("x:%f y:%f z:%f \n",worldCoords[k].x,worldCoords[k].y,worldCoords[k].z);
				}

				double dptp = distPlaneToPoint(worldCoords[0],worldCoords[1] ,worldCoords[2] , center);
                        	printf("ptpdist : %f Tank point: x:%f y:%f z:%f\n",dptp, center.x,center.y,center.z);
				if(dptp < sphdist){        
					printf("ptpdist : %f , sphdist %f\n",dptp, sphdist);
					return true;
                        	        printf("collide true\n");
                        	}
			}
                }
        }

        return false;

	/*
	Point ax = Point(10,10,0);
	Point bx = Point(1,0,0);
	Point cx = Point(0,1,1);
	Point dx = Point(0,10,15);
	
	printf("%f\n",distPlaneToPoint(ax,bx,cx,dx));
	*/

	/*
	double targetRadius;
	double tankRadius = distance(tank->getFurthestPoint(), tank->center);
	double tankProjCenterDistance;
	double projTankCenterDistance; 
	double projRadius;
	double tarRadius;
	*/

	// getFurthestPoint (alternately radius variable) should return point of each object furthest from center  

	// check tank & building collision
	// projectile collision
	
	/*
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
 	*/

	// cases 1 and 2

	/*		
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
		
	*/
	//printf("collision detect start");

}




