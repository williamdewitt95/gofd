#include "collisions.h"

int intersect3D_SegmentPlane( LineSeg seg, Polygon3d poly, Point &I ){//only works for rectangles
	double x=0,y=0,z=0;
	int imin = std::numeric_limits<int>::min(); // minimum value
	int imax = std::numeric_limits<int>::max();
	double maxX=imin, maxY=imin, maxZ=imin;
	double minX=imax, minY=imax, minZ=imax;

	std::vector<Point> points = poly.getWorldPoints().getPoints();
	// printf("intersect\n");
	for(int i=0;i<points.size();i++){
		// printf("i: %d\n",i);
		x += points.at(i)[0];
		y += points.at(i)[1];
		z += points.at(i)[2];
		if(points.at(i)[0] > maxX)
			maxX = points.at(i)[0];
		if(points.at(i)[0] < minX)
			minX = points.at(i)[0];
		if(points.at(i)[1] > maxY)
			maxY = points.at(i)[1];
		if(points.at(i)[1] < minY)
			minY = points.at(i)[1];
		if(points.at(i)[2] > maxZ)
			maxZ = points.at(i)[2];
		if(points.at(i)[2] < minZ)
			minZ = points.at(i)[2];

	}

	x = x/(points.size()*1.0);
	y = y/(points.size()*1.0);
	z = z/(points.size()*1.0);
	Point p = Point(x,y,z);
	
	// printf("poly.world.center (%f,%f,%f) ",p[0],p[1],p[2]);
	// printf("seg.p1 (%f,%f,%f) ",seg.p1[0],seg.p1[1],seg.p1[2]);
	// printf("seg.p2 (%f,%f,%f) ",seg.p2[0],seg.p2[1],seg.p2[2]);

    Vector u = Vector(seg.p1, seg.p2);
    Vector w = Vector(seg.p1[0] - p[0], seg.p1[1]-p[1], seg.p1[2] - p[2]);

    Vector normal = poly.getWorldPoints().getNormal();
    double D = normal.dot(u);
    double N = -normal.dot(w);

    if (fabs((float)D) < 0) {           // segment is parallel to plane
        if (N == 0)                      // segment lies in plane
            return 2;
        else
            return 0;                    // no intersection
    }

    // they are not parallel
    // compute intersect param
    double sI = N / D;
    if (sI < 0 || sI > 1)
        return 0;                        // no intersection
    // printf(" working  ");
    I = Point(seg.p1[0]+sI*u[0], seg.p1[1]+sI*u[1], seg.p1[2]+sI*u[2]);                  // compute segment intersect point
    if(points.size()==5){//rectangle
   			// printf("XXX\t%.25f > %.25f && %f < %f && %.3f > %.3f && %.13f < %.13f\n",maxY, I[1],minY,I[1],maxZ,I[2],minZ,I[2]);
    		if(maxY < I[1] || minY > I[1] || (float)maxZ < (float)I[2] || (float)minZ > (float)I[2] || maxX < I[0] || minX > I[0]){
    			// printf("outside, doesn't collide 3\n");
    			return 3;
    		}
    		else{
    			return 1;
    		}
    }
    if(points.at(0)[0] != points.at(2)[0]){
    	// printf("XXXXXXXX, %f, %f, %f        %f, %f, %f\n",points.at(0)[0],points.at(0)[1],points.at(0)[2],points.at(2)[0],points.at(2)[1],points.at(2)[2]);
    	if(points.size()==5){//rectangle
   			// printf("XXX\t%.25f > %.25f && %f < %f && %.3f > %.3f && %.13f < %.13f\n",maxY, I[1],minY,I[1],maxZ,I[2],minZ,I[2]);
    		if(maxY < I[1] || minY > I[1] || (float)maxZ < (float)I[2] || (float)minZ > (float)I[2] || maxX < I[0] || minX > I[0]){
    			// printf("outside, doesn't collide 3\n");
    			return 3;
    		}
    		else{
    			return 1;
    		}
    	}
    }
    else if(points.at(0)[1] != points.at(2)[1]){
    	// printf("YYYYYYYY");
    	if(points.size()==5){//rectangle
  			// printf("YYY\t%.3f < %.3f && %.3f > %.3f && %.3f > %.3f && %.3f < %.3f\n",maxX, I[0],minX,I[0],maxZ,I[2],minZ,I[2]);
    		if(maxX < I[0] || minX > I[0] || maxZ < I[2] || minZ > I[2]){
    			// printf("outside, doesn't collide 4\n");
    			return 4;
    		}
    		else{
    			return 1;
    		}
    	}
    }
    else{
		if(points.size()==5){//rectangle
    		if(maxX < I[0] || minX > I[0] || maxY < I[1] || minY > I[1]){
    			//printf("outside, doesn't collide 5\n");
    			return 5;
    		}
    		else{
    			return 1;
    		}
    	}
    }
	return 1;
}

void collisionTest(){
	// printf("\ncollision test\n");

	// printf("building center %f,%f,%f\n",buildings.at(0));
	for(int j=0;j<projectiles.size();j++){
		Projectile * tempProjectile = projectiles.at(j);
		if(tempProjectile->state == Projectile::MOVING && !tempProjectile->invincibility){
			for(int k=0; k<buildings.size();k++){

				
				double sq = sqrt((buildings.at(k)->center[0] - tempProjectile->center[0])*(buildings.at(k)->center[0] - tempProjectile->center[0])
					+(buildings.at(k)->center[1] - tempProjectile->center[1])*(buildings.at(k)->center[1] - tempProjectile->center[1])
					+(buildings.at(k)->center[2] - tempProjectile->center[2])*(buildings.at(k)->center[2] - tempProjectile->center[2]));
				if(sq > buildings.at(k)->maxBuildingWidth*2)
					continue;
				// printf("~~~~~~~~~~~~~k: %d    %f,%f,%f\n",k,buildings.at(k)->center[0], buildings.at(k)->center[1], buildings.at(k)->center[2]);
				LineSeg testLine = LineSeg(tempProjectile->oldCenter,tempProjectile->center);

				std::vector<Polygon3d> buildingSides = buildings.at(k)->getBoundingBox();
				Point intersect;
				for(int i=0; i<buildingSides.size();i++){
					buildingSides.at(i).setCenter(buildings.at(k)->center);
					int a = intersect3D_SegmentPlane(testLine, buildingSides.at(i), intersect);
					// printf("%d\t",a);
					if(a==1){
						// printf("\nintersect at (%f,%f,%f)\n",intersect[0], intersect[1], intersect[2]);
					    tempProjectile->setExploding(intersect);
					    // printf("\nprojectile state %d, velocity %f)\n",tempProjectile->state, tempProjectile->velocity);
					   	continue;
						// exit(0);
					}
					else{
						// printf("\t%d\n",a);
					}
				}
			}
			double sq = sqrt((tank->center[0] - tempProjectile->center[0])*(tank->center[0] - tempProjectile->center[0])
				+(tank->center[1] - tempProjectile->center[1])*(tank->center[1] - tempProjectile->center[1])
				+(tank->center[2] - tempProjectile->center[2])*(tank->center[2] - tempProjectile->center[2]));
			if(sq < 50.0){		
				LineSeg testLine = LineSeg(tempProjectile->oldCenter, tempProjectile->center);
				std::vector<Polygon3d> tankSides = tank->boundingBox();
				Point intersect;
				for(int i=0;i<tankSides.size();i++){
					tankSides.at(i).setCenter(tank->center);
					int a = intersect3D_SegmentPlane(testLine, tankSides.at(i), intersect);
					if(a==1){
						tempProjectile->setExploding(intersect);
						// printf("Hit!\n\n\n");
						tank->health-=10;
						break;
					}

				}
			}
			sq = sqrt((ai_tank->tank->center[0] - tempProjectile->center[0])*(ai_tank->tank->center[0] - tempProjectile->center[0])
					+(ai_tank->tank->center[1] - tempProjectile->center[1])*(ai_tank->tank->center[1] - tempProjectile->center[1])
					+(ai_tank->tank->center[2] - tempProjectile->center[2])*(ai_tank->tank->center[2] - tempProjectile->center[2]));
			if(sq < 50.0){
				// printf("sq: %f \n",sq);
				LineSeg testLine = LineSeg(tempProjectile->oldCenter, tempProjectile->center);
				std::vector<Polygon3d> tankSides = ai_tank->tank->boundingBox();
				Point intersect;
				// printf("tankSides.size() %d     ",(int)tankSides.size());
				for(int i=0;i<tankSides.size();i++){
					tankSides.at(i).setCenter(ai_tank->tank->center);
					int a = intersect3D_SegmentPlane(testLine, tankSides.at(i), intersect);
					if(a==1){
						tempProjectile->setExploding(intersect);
						// printf("Hit!\n\n\n");
						GLOBAL.score++;
						break;
					}

				}
			}
		}

	}
}