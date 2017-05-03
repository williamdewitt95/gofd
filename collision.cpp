#include "collision.h"
//chris:Struct introduces the paramaters of a plane
struct plane {
	double a;
	double b;
	double c;
	double d;
};

//devin:when needing to compare relative distance
// and the actual distance is not needed
// it is faster to simply calculate the distance 
// without the squareroot

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
devin
Distance function usage
	Point *a = new Point(0,0,0);
        Point *b = new Point(0,0,5);
        cout << "distance between a and b: " << distance(*a,*b) << "\n";
	This will print the value 5
*/
//incase actual ditance is needed we use this function
//Uses the Point class
double distance(Point a, Point b){
	return sqrt(distSquare(a,b));

}

//devin \:Uses the Vector class
double distance(Vector a, Vector b){

        return sqrt(distSquare(a,b));

}
//devin:c is the center point of sphere, n is normal of plane, p is point on plane
bool sphereToPlane(Point c, double radius,Vector n, Point p){
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

//chris: Takes in 4 points.  3 points of which are on the plane
// 4th point not ont he plane.  The three points will be converted
// to parameters of a plane and then the equation for the plane
// will be taken and the distance between point 4 and a orthogonal point
// is calculated
double distPlaneToPoint (Point a, Point b, Point c, Point d)
{
	plane tmp;
	Vector v1, v2, v3;
	v1 = Vector (a,b);
	v2 = Vector (a,c);
	v3 = v1.cross (v2);
	tmp.a = v3.x; tmp.b = v3.y; tmp.c = v3.z;
	//devin:calculates final point of the plane definition needed to calculate distance
	tmp.d = -1*v3.x*a.x + -1*v3.y*a.y + -1*v3.z*a.z;
	return abs(tmp.a*d.x + tmp.b*d.y + tmp.c*d.z + tmp.d)/(sqrt(tmp.a*tmp.a + tmp.b*tmp.b + tmp.c*tmp.c));
}


bool collisionDetect(Point center, double sphdist, std::vector<Building*>& buildings, std::vector<Projectile*>& projectiles){

	//devin:iterate through all the buildings to check if the tank is close enough to collide
	for(int i = 0; i < buildings.size(); i++){

                //devin:tbDist has the distance between the center point and the buildings center
                double tbDist = distance(center,buildings[i]->center);
		std::vector<Polygon3d> sides = buildings[i]->boundingBox();
		//devin:sides is a set of polygons that represent the collision box of the building
                if(tbDist < sphdist + buildings[i]->maxBuildingWidth/2+5){
                        //devin:this sees if the bounding sphere of the tank is intersecting the colliding sphere
			// of the building. If true we further check extra collision parameters
			
			for(int j = 0; j < sides.size(); j++){
				//devin: we check this extra collision information with the other sides of the
				// building
				std::vector<Point> worldCoords = sides[j].getPoints();
				//devin: This vector of Vector objects stores the world transformed points

				double dptp = distPlaneToPoint(worldCoords[0],worldCoords[1] ,worldCoords[2] , center);
                        	//devin: This is the distance from the tanks center to the plan defined in worldCoords
				if(dptp < sphdist){        
					//devin: If the distance is smaller than the radius of the sphere we know that the plane 
					// is close enough for the tank to intersect the plane
					return true;
                        	}
			}
                }
        }

        return false;

}

