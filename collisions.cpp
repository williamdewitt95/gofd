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
	//This loop is to test every projectile and see if it has hit anything
	//If it has, depending on what it hit, we can do certain things, usually ending with it exploding
	for(int j=0;j<projectiles.size();j++){
		Projectile * tempProjectile = projectiles.at(j);

		//Only do a check if the projectile is moving and so able to hit things
		if(tempProjectile->state == Projectile::MOVING && !tempProjectile->invincibility){
			//====================================================================================================================================
			//targets collision check
			for(int k=0; k<targets.size();k++){
				//only check the target if it is not already been hit
				if(targets[k]->state == Target::DEAD)
					continue;

				double dist = Vector(targets[k]->center,tempProjectile->center).length();

				if(dist > targets.at(k)->radius*2.0)
					continue; // skip if they are so far away that there is no chance of them colliding

				//Now we check if there is a line between the two locations of the projectile to see if it passed through anything
				LineSeg testLine = LineSeg(tempProjectile->oldCenter,tempProjectile->center);

				std::vector<Polygon3d> buildingSides = targets.at(k)->getBoundingBox();
				Point intersect;
				for(int i=0; i<buildingSides.size();i++){
					int a = intersect3D_SegmentPlane(testLine, buildingSides.at(i), intersect);
					if(a==1){
					    tempProjectile->setExploding(intersect);
					    GLOBAL.score+=2;
					    targets[k]->state = Target::DEAD;
					    break;
					}
				}
				if(tempProjectile->state != Projectile::MOVING) // if it hit something, stop checking if it hit another building
					break;
			}
			if(tempProjectile->state != Projectile::MOVING) // if it hit something, move on to the next projectile
				continue;

			//====================================================================================================================================
			//building walls collision check
			for(int k=0; k<buildings.size();k++){

				double dist = Vector(buildings[k]->center,tempProjectile->center).length();

				if(dist > buildings.at(k)->maxBuildingWidth*2)
					continue; // skip if they are so far away that there is no chance of them colliding

				//Now we check if there is a line between the two locations of the projectile to see if it passed through anything
				LineSeg testLine = LineSeg(tempProjectile->oldCenter,tempProjectile->center);

				std::vector<Polygon3d> buildingSides = buildings.at(k)->getBoundingBox();
				Point intersect;
				for(int i=0; i<buildingSides.size();i++){
					int a = intersect3D_SegmentPlane(testLine, buildingSides.at(i), intersect);
					if(a==1){
					    tempProjectile->setExploding(intersect);
					    break;
					}
				}
				if(tempProjectile->state != Projectile::MOVING) // if it hit something, stop checking if it hit another building
					break;
			}
			if(tempProjectile->state != Projectile::MOVING) // if it hit something, move on to the next projectile
				continue;

			//====================================================================================================================================
			//Player tank collision check
			double dist = Vector(tank->center,tempProjectile->center).length();
			if(dist < 30.0){
				LineSeg testLine = LineSeg(tempProjectile->oldCenter, tempProjectile->center);
				std::vector<Polygon3d> tankSides = tank->getBoundingBox();
				Point intersect;
				for(int i=0;i<tankSides.size();i++){
					int a = intersect3D_SegmentPlane(testLine, tankSides.at(i), intersect);
					if(a==1){
						tempProjectile->setExploding(intersect);
						tank->health-=10;
						break;
					}

				}
			}
			if(tempProjectile->state != Projectile::MOVING) // if it hit something, move on to the next projectile
				continue;

			//====================================================================================================================================
			//AI tank collision check
			for(int k=0; k<ai_tanks.size();k++){

				double dist = Vector(ai_tanks[k]->tank->center,tempProjectile->center).length();

				if(dist > 30.0)
					continue; // skip if they are so far away that there is no chance of them colliding

				//Now we check if there is a line between the two locations of the projectile to see if it passed through anything
				LineSeg testLine = LineSeg(tempProjectile->oldCenter,tempProjectile->center);

				std::vector<Polygon3d> buildingSides = ai_tanks.at(k)->tank->getBoundingBox();
				Point intersect;
				for(int i=0; i<buildingSides.size();i++){
					int a = intersect3D_SegmentPlane(testLine, buildingSides.at(i), intersect);
					if(a==1){
					    tempProjectile->setExploding(intersect);
					    GLOBAL.score += 10;
					    break;
					}
				}
				if(tempProjectile->state != Projectile::MOVING) // if it hit something, stop checking if it hit another building
					break;
			}
			if(tempProjectile->state != Projectile::MOVING) // if it hit something, move on to the next projectile
				continue;
		}

	}
}