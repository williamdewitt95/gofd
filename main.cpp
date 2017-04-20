#include <limits>
#include <GL/glew.h> 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <math.h>
#include <vector>
#include <GL/glut.h>
#include <iostream>
#include "globals.h"
#include "building.h"
#include "projectile.h"
#include "tank.h"
#include "target.h"
#include "ai.h"
#include "hud.h"
using std::cin;
using std::cout;

std::vector<Building*> buildings; // must be a pointer so that we dont try to allocated GL things before it has been inited
std::vector<Target*> targets;
double camMove_forward = 0;
double camMove_strafe = 0;
double camMove_vert = 0;
const double camMove_speed = 0.25 / 2.0;
double tankAccel = 0;
double tankScale = 0;
double tankBaseRotate = 0;
double tankTurretRotate = 0;
double tankCannonRotate = 0;
bool laserOn = true;
int cameraMode = 0;
Tank * tank;
bool orthoView = false;
bool aerial = false;

int oldTime=0.0;
float actualfps, fps=0.0;

AI_Tank * ai_tank;
std::vector<Projectile*> projectiles;

void mouseButtons(int but,int state,int x,int y){
	//scaleMouse(x,y);

	//this is still needed since we are expecting to measure from the bottom left with how i set things up but the mouse is reported from the top left
	y=GLOBAL.WINDOW_MAX_Y-y;

	if(but==0 && state==GLUT_DOWN){
		//left mouse button
		tank->shoot();
	}else if(but==2 && state==GLUT_DOWN){
		//right mouse button
	}else if(but==3 && state==GLUT_DOWN){
		//scroll up
	}else if(but==4 && state==GLUT_DOWN){
		//scroll down
	}else{
		if(state == GLUT_DOWN)printf("Unknown Mouse Button %d\n",but);
	}
}
void passiveMouseMovement(int x,int y){
	//x and y are window cordinates
	//it is up to us to get deltas
	cameraMovement(x,y,tank->center,cameraMode);
	tank->turretFollowMouse(x, y,cameraMode);
}
void mouseMovement(int x,int y){
	//x and y are window cordinates
	//it is up to us to get deltas
	// FPS_CameraMovement(x,y);
}

void gameEngine(){
	for(int x=0; x<buildings.size(); x++)
		buildings[x]->update();

	for(int x=0; x<targets.size();x++)
		targets[x]->update();
	
	GLOBAL.CAMERA_POS.z += camMove_vert;
	GLOBAL.CAMERA_POS.x += camMove_forward * cos(GLOBAL.CAMERA_ANGLE_HORIZONTAL*PI/180.0);
	GLOBAL.CAMERA_POS.y += camMove_forward * -sin(GLOBAL.CAMERA_ANGLE_HORIZONTAL*PI/180.0);

	GLOBAL.CAMERA_POS.x += camMove_strafe * sin(GLOBAL.CAMERA_ANGLE_HORIZONTAL*PI/180.0);
	GLOBAL.CAMERA_POS.y += camMove_strafe * cos(GLOBAL.CAMERA_ANGLE_HORIZONTAL*PI/180.0);

	//iterate tank properties
	tank->update(tankBaseRotate, tankTurretRotate, tankCannonRotate, cameraMode, tankAccel); // the things below need to be moved into this function
	ai_tank->updateTank();
	ai_tank->nearbyTarget(tank);
	
	GLOBAL.LIGHTS[0].position[0]=tank->center.x;
	GLOBAL.LIGHTS[0].position[1]=tank->center.y;
	GLOBAL.LIGHTS[0].position[2]=tank->center.z+5;

	GLOBAL.LIGHTS[1].position[0]=tank->center.x;
	GLOBAL.LIGHTS[1].position[1]=tank->center.y;

	GLOBAL.LIGHTS[2].position[0]=tank->center.x;
	GLOBAL.LIGHTS[2].position[1]=tank->center.y;
	// GLOBAL.LIGHTS[2].position[2]=tank->center.z+10;




	for(int i=projectiles.size()-1; i >=0 ; i--){
		projectiles[i]->update();
		if(projectiles[i]->state==Projectile::DEAD)
			projectiles.erase(projectiles.begin()+i);
	}

}

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
    			printf("outside, doesn't collide 5\n");
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




void drawHud() {//to draw the 2d hud on 3d scene
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // reset the projection style
	gluOrtho2D(0.0,100.0,100.0,0.0); // simple ortho

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//draw 2D stuff
	drawHealthBar(*tank);
	drawCooldownBar(*tank);
	drawScore();

	showFPS(fps, oldTime, actualfps);
}


void drawWorld(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // reset the values
	double aspect = (GLOBAL.WINDOW_MAX_X/(double)GLOBAL.WINDOW_MAX_Y);
	
	if(!orthoView){
	gluPerspective(90,aspect,0.1,1000);
	{
		double temp[3]={
			GLOBAL.CAMERA_POS.x + GLOBAL.CAMERA_LOOK_VECTOR.x,
			GLOBAL.CAMERA_POS.y + GLOBAL.CAMERA_LOOK_VECTOR.y,
			GLOBAL.CAMERA_POS.z + GLOBAL.CAMERA_LOOK_VECTOR.z
		};
		
		if(!aerial){
		gluLookAt(
				GLOBAL.CAMERA_POS.x,GLOBAL.CAMERA_POS.y,GLOBAL.CAMERA_POS.z,
				temp[0],temp[1],temp[2],
				0,0,1
				);
		}
		else{
			gluLookAt(450.0, 450.0, -600.0, 450.0 , 450.0, 0.0, 0.0, -1.0, -1.0);
		}
	}
	}
	
	else{
		glOrtho(-500.0, 500.0, -500.0, 500.0, 0.1, 1000);{
			gluLookAt(450.0, 450.0, 800.0, 450.0 , 450.0, 0.0, 0.0, -1.0, -1.0);
		}
	}

	
	glMatrixMode(GL_MODELVIEW);

	for(int x=0; x<buildings.size(); x++)
		buildings[x]->draw();

	tank->draw();
	ai_tank->tank->draw();

	for(int i=0; i<projectiles.size();i++){
		projectiles[i]->draw();
	}

	for(int x=0; x<targets.size(); x++)
	    targets[x]->draw();

	//tank->drawHealthBar(tank->health);
}

void drawMinimap(){
	double height,width;
	height = 100;
	width = GLOBAL.WINDOW_MAX_X/(double)GLOBAL.WINDOW_MAX_Y * height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // reset the projection style
	glOrtho(-width,width , -height,height , -5.0,500.0); // simple ortho - left,right,bottom,top,near,far
	gluLookAt(
		tank->center.x,tank->center.y,400,
		tank->center.x,tank->center.y,0,
		0,1,0
		);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	{//Make a black polygon to draw our world on top of so the regular world does not bleed through
		double &x=tank->center.x;
		double &y=tank->center.y;
		glColor3ub(0,0,0);
		glBegin(GL_POLYGON);
			glVertex3d(x-width,y-height,-50);
			glVertex3d(x+width,y-height,-50);
			glVertex3d(x+width,y+height,-50);
			glVertex3d(x-width,y+height,-50);
		glEnd();
	}

	for(int x=0; x<buildings.size(); x++)
		buildings[x]->draw();

	tank->draw();
	ai_tank->tank->draw();
}

void display(){
	glEnable(GL_LIGHTING);
	updateLights();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,GLOBAL.WINDOW_MAX_X,GLOBAL.WINDOW_MAX_Y);
	drawWorld();
	collisionTest();

	
	//===============================================================================
	glDisable(GL_LIGHTING);

	glClear(GL_DEPTH_BUFFER_BIT);
	drawHud();

	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,GLOBAL.WINDOW_MAX_X/4,GLOBAL.WINDOW_MAX_Y/4);
	drawMinimap();


	glFlush();
	glutSwapBuffers();
	glutPostRedisplay(); //always say we want a redraws
}

void keyboardButtons(unsigned char key, int x, int y){
	if(key == 'q' || key == 'Q'){
		exit(0);
	}else if(key == 'w' || key == 'W'){
		camMove_forward += camMove_speed;
	}else if(key == 's' || key == 'S'){
		camMove_forward -= camMove_speed;
	}else if(key == 'a' || key == 'A'){
		camMove_strafe += camMove_speed;
	}else if(key == 'd' || key == 'D'){
		camMove_strafe -= camMove_speed;
	}else if(key == 'i' || key == 'I'){
		tankAccel += 0.005;
	}else if(key == 'j' || key == 'J'){
		tankBaseRotate += 2;
	}else if(key == 'k' || key == 'K'){
		tankAccel -= 0.005;
	}else if(key == 'l' || key == 'L'){
		tankBaseRotate -= 2;
	}else if(key == 'u' || key == 'U'){
		tankTurretRotate += 2;
	}else if(key == 'o' || key == 'O'){
		tankTurretRotate -= 2;
	}else if(key == 'n' || key == 'N'){
		tankScale -= 0.05;
	}else if(key == 'm' || key == 'M'){
		tankScale += 0.05;
	}else if(key == 'z' || key == 'Z'){
		if(cameraMode>1){//currently looking at three camera modes that we switch between
			cameraMode = 0;
		}
		else{
			cameraMode++;
		}
	}else if(key == '-' || key == '_'){
		tankCannonRotate -= 2;
	}else if(key == '=' || key == '+'){
		tankCannonRotate += 2;
	}else if(key == '8'){
		tank->laser = !tank->laser;
	//end of tank controls
	}else if(key == 'c' || key == 'C'){
		camMove_vert += camMove_speed;
	}else if(key == ' '){
		camMove_vert -= camMove_speed;
	}else if(key == 'x' || key == 'X'){
		tank->shoot();
	}else if(key == 'y' || key == 'Y'){
		if(tank->health >= 10)
			tank->health = tank->health-10;
		glutPostRedisplay();
		printf("%d\n", tank->health);
	}else if(key == 'v' || key == 'V' ){
		orthoView = !orthoView;
	}else if(key == 'r' || key == 'R'){
		aerial = !aerial;
	}else{
		printf("Unknown Key Down %d\n",key);
	}

	if(camMove_forward > camMove_speed)
		camMove_forward = camMove_speed;
	if(camMove_forward < -1 * camMove_speed)
		camMove_forward = -1 * camMove_speed;

	if(camMove_strafe > camMove_speed)
		camMove_strafe = camMove_speed;
	if(camMove_strafe < -1 * camMove_speed)
		camMove_strafe = -1 * camMove_speed;

	if(camMove_vert > camMove_speed)
		camMove_vert = camMove_speed;
	if(camMove_vert < -1 * camMove_speed)
		camMove_vert = -1 * camMove_speed;
}
void keyboardButtonsUp(unsigned char key, int x, int y){
	if(key == 'q' || key == 'Q'){
		exit(0);
	}else if(key == 'w' || key == 'W'){
		camMove_forward -= camMove_speed;
	}else if(key == 's' || key == 'S'){
		camMove_forward += camMove_speed;
	}else if(key == 'a' || key == 'A'){
		camMove_strafe -= camMove_speed;
	}else if(key == 'd' || key == 'D'){
		camMove_strafe += camMove_speed;
	//tank controls
	}else if(key == 'i' || key == 'I'){
		tankAccel -= 0.005;
	}else if(key == 'j' || key == 'J'){
		tankBaseRotate -= 2;
	}else if(key == 'k' || key == 'K'){
		tankAccel += 0.005;
	}else if(key == 'l' || key == 'L'){
		tankBaseRotate += 2;
	}else if(key == 'u' || key == 'U'){
		tankTurretRotate -= 2;
	
	}else if(key == 'n' || key == 'N'){
		tankScale += 0.05;
	}else if(key == 'm' || key == 'M'){
		tankScale -= 0.05;
	}else if(key == '-' || key == '_'){
		tankCannonRotate += 2;
	}else if(key == '=' || key == '+'){
		tankCannonRotate -= 2;
	//end of tank controls
	}else if(key == 'c' || key == 'C'){
		camMove_vert -= camMove_speed;
	}else if(key == ' '){
		camMove_vert += camMove_speed;
	}else if(key == 'x' || key == 'X' || key == 'y' || key == 'Y'){
		//do nothing, but stop printing unknown key
	}else{
		printf("Unknown Key Up %d\n",key);
	}

	if(camMove_forward > camMove_speed)
		camMove_forward = camMove_speed;
	if(camMove_forward < -1 * camMove_speed)
		camMove_forward = -1 * camMove_speed;

	if(camMove_strafe > camMove_speed)
		camMove_strafe = camMove_speed;
	if(camMove_strafe < -1 * camMove_speed)
		camMove_strafe = -1 * camMove_speed;

	if(camMove_vert > camMove_speed)
		camMove_vert = camMove_speed;
	if(camMove_vert < -1 * camMove_speed)
		camMove_vert = -1 * camMove_speed;
}
void keyboardButtons_special(int key,int x,int y){
	if(key == GLUT_KEY_UP){
	}else if(key == GLUT_KEY_DOWN){
	}else if(key == GLUT_KEY_LEFT){
	}else if(key == GLUT_KEY_RIGHT){
	}else if(key == GLUT_KEY_PAGE_UP){
	}else if(key == GLUT_KEY_PAGE_DOWN){
	}else{
		printf("Unknown Special Key Down %d\n",key);
	}
}
void keyboardButtonsUp_special(int key,int x,int y){
	if(key == GLUT_KEY_UP){
	}else if(key == GLUT_KEY_DOWN){
	}else if(key == GLUT_KEY_LEFT){
	}else if(key == GLUT_KEY_RIGHT){
	}else if(key == GLUT_KEY_PAGE_UP){
	}else if(key == GLUT_KEY_PAGE_DOWN){
	}else{
		printf("Unknown Special Key Up %d\n",key);
	}
}

int main(int argc,char** args){
	glutInit(&argc, args);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA | GLUT_ALPHA);

	glutInitWindowPosition(0,0);
	glutInitWindowSize(GLOBAL.WINDOW_MAX_X,GLOBAL.WINDOW_MAX_Y);
	glutCreateWindow("Pendulum");

	glClearColor(0,0,0,0);

	glutReshapeFunc(windowResize);
	glutDisplayFunc(display);
	glutIdleFunc(gameEngine);
	glutPassiveMotionFunc(passiveMouseMovement);
	glutMotionFunc(mouseMovement);
	glutMouseFunc(mouseButtons);
	glutKeyboardFunc(keyboardButtons);
	glutKeyboardUpFunc(keyboardButtonsUp);
	glutSpecialFunc(keyboardButtons_special);
	glutSpecialUpFunc(keyboardButtonsUp_special);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	// glEnable(GL_LIGHT2);
	// glEnable(GL_LIGHT3);
	// glEnable(GL_LIGHT4);
	// glEnable(GL_LIGHT5);
	// glEnable(GL_LIGHT6);
	// glEnable(GL_LIGHT7);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE); // make the lighting track the color of objects

	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );

	//let people use random numbers without worrying about how to seed things
	srand(time(NULL));

	// enable blending to have translucent materials
	// you must draw objects back to front to get proper blending
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glEnable (GL_BLEND); glBlendFunc (GL_ONE, GL_ONE);

	for(int x=0;x<NUM_BLOCKS_WIDE;x++){
		for(int y=0;y<NUM_BLOCKS_WIDE;y++){
			buildings.push_back(new Building(Point(
					Building::distanceBetweenBuildings*x,
					Building::distanceBetweenBuildings*y,
					0)
				));

			int randSide = (rand()/(double)RAND_MAX) * 4;
			double randomHeight = rand() / (double)RAND_MAX;
			double maxHeight = buildings[buildings.size()-1]->getBoundingBox()[0][0].z;
			double targetCenter = randomHeight * (3.0*maxHeight/4.0) + (maxHeight/8.0); //randomly spawns in the middle 3/4 of the building

			if(randSide == 0) {//"north" wall
				targets.push_back(new Target(Point(
					Building::distanceBetweenBuildings*x,
					Building::distanceBetweenBuildings*y - (Building::maxBuildingWidth)/2.0 - 0.55,
					targetCenter)
				));
			} else if(randSide == 1) {//"west"
				Target *tDawg = new Target(Point(
					Building::distanceBetweenBuildings*x + (Building::maxBuildingWidth)/2.0 + 0.55,
					Building::distanceBetweenBuildings*y - (Building::maxBuildingWidth)/32.0,
					targetCenter));
				(*tDawg).setRotation(90.0);
				targets.push_back(tDawg);
			} else if(randSide == 2) {//"south
				targets.push_back(new Target(Point(
					Building::distanceBetweenBuildings*x,
					Building::distanceBetweenBuildings*y + (Building::maxBuildingWidth)/2.0 + 0.55,
					targetCenter)
				));
			} else if(randSide == 3) {//"east"
				Target *tDawg = new Target(Point(
					Building::distanceBetweenBuildings*x - (Building::maxBuildingWidth)/2.0 - 0.55,
					Building::distanceBetweenBuildings*y - (Building::maxBuildingWidth)/32.0,
					targetCenter));
				(*tDawg).setRotation(90.0);
				targets.push_back(tDawg);
			} else {
				std::cout << "SOMETHING HAS GONE HORRIBLY WRONG" << std::endl;
				exit(0);
			}
		}
	}

	tank = new Tank(Point(0, Building::maxBuildingWidth/2.0 + Building::streetWidth/2.0, 0));
	ai_tank = new AI_Tank(new Tank(
		Point(Building::maxBuildingWidth/2.0 + Building::streetWidth/2.0,
			Building::maxBuildingWidth/2.0 + Building::streetWidth/2.0,
			0)
		));
	oldTime = glutGet(GLUT_ELAPSED_TIME);

	glutMainLoop();
	return 0;
}
