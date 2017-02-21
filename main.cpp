<<<<<<< HEAD
#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>

using namespace std;

float camX;
float camY;
float camZ;

const int WINDOW_MAX_X = 500;
const int WINDOW_POSITION_X = 200;
const int WINDOW_MAX_Y = 500;
const int WINDOW_POSITION_Y = 200;

const float WORLD_COORD_MIN_X = 0.0;
const float WORLD_COORD_MAX_X = 400.0;
const float WORLD_COORD_MIN_Y = 0.0;
const float WORLD_COORD_MAX_Y = 400.0;

void myGlutInit(int argc, char** argv){

	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_MAX_X,WINDOW_MAX_Y);
	glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
	glutCreateWindow("Game of Drones");

	glEnable(GL_DEPTH_TEST);
}

void init(){

        glClearColor ( 0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	glFlush();

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
	gluPerspective(45,1.0,1.5,900);
	glMatrixMode(GL_MODELVIEW);

}

void display(){

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(100,100,100, 0.0,0.0,0.0, 0.0,0.0,1.0);

        glPointSize(1.0);

	glColor3f(1.0,1.0,1.0);

	glBegin(GL_LINES);
                glVertex3f(-50,0,0);
                glVertex3f(50,0,0);
        glEnd();

        glBegin(GL_LINES);
                glVertex3f(0,-50,0);
                glVertex3f(0,50,0);
        glEnd();

        glBegin(GL_LINES);
                glVertex3f(0,0,-50);
                glVertex3f(0,0,50);
        glEnd();

	glBegin(GL_LINES);
	for(int i = 0; i < 21; i++){
		for(int j = 0; j < 21; j++){
			glVertex3i(-50,(j*5)-50,0);
			glVertex3i(50,(j*5)-50,0);
			glVertex3i((j*5)-50,-50,0);
                        glVertex3i((j*5)-50,50,0);
		}
	}
	glEnd();

	glFlush();

}

void mouse(int button, int state, int x, int y){

}

void keyboard(unsigned char key, int x, int y){

	if(key == 'q'){
		exit(0);
	}

}

void reshape(int w, int h){

}

int main(int argc, char** argv){

        myGlutInit(argc,argv);
        init();

        glutMouseFunc(mouse);
        glutKeyboardFunc(keyboard);
        glutDisplayFunc(display);
 	glutReshapeFunc(reshape);
	//glutIdleFunc();
        glutMainLoop();

=======
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <math.h>
#include <vector>
#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>
#include "globals.h"
#include "building.h"
#include "projectile.h"
#include "tank.h"
#include "target.h"
#include "ai.h"
using std::cin;
using std::cout;

std::vector<Building*> buildings; // must be a pointer so that we dont try to allocated GL things before it has been inited
std::vector<Target*> targets;
double camMove_forward = 0;
double camMove_strafe = 0;
double camMove_vert = 0;
const double camMove_speed = 0.25 / 2.0;
double tankSpeed = 0;
double tankScale = 0;
double tankBaseRotate = 0;
double tankTurretRotate = 0;
double tankCannonRotate = 0;
bool laserOn = true;
int cameraMode = 0;
Tank * tank;

AI_Tank * ai_tank;
std::vector<Projectile*> projectiles;

void mouseButtons(int but,int state,int x,int y){
	//scaleMouse(x,y);

	//this is still needed since we are expecting to measure from the bottom left with how i set things up but the mouse is reported from the top left
	y=GLOBAL.WINDOW_MAX_Y-y;

	if(but==0 && state==GLUT_DOWN){
		//left mouse button
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
	//printf("Here\n");
	for(int x=0; x<targets.size();x++)
		targets[x]->update();
	GLOBAL.CAMERA_POS.z += camMove_vert;
	GLOBAL.CAMERA_POS.x += camMove_forward * cos(GLOBAL.CAMERA_ANGLE_HORIZONTAL*PI/180.0);
	GLOBAL.CAMERA_POS.y += camMove_forward * -sin(GLOBAL.CAMERA_ANGLE_HORIZONTAL*PI/180.0);

	GLOBAL.CAMERA_POS.x += camMove_strafe * sin(GLOBAL.CAMERA_ANGLE_HORIZONTAL*PI/180.0);
	GLOBAL.CAMERA_POS.y += camMove_strafe * cos(GLOBAL.CAMERA_ANGLE_HORIZONTAL*PI/180.0);

	//iterate tank properties
	tank->update(tankSpeed, tankBaseRotate, tankTurretRotate, tankCannonRotate, cameraMode); // the things below need to be moved into this function
	ai_tank->updateTank();
	ai_tank->nearbyTarget(tank);
	

	for(int i=0; i < projectiles.size(); i++){
		projectiles[i]->update();
	}

	
	/*
		Apply vechile transformations:
	 *
	 * 	 *		*update center points (world coords)
	 * 	 	 *		*transform vertices (local coords) 
	 * 	 	 	 *
	 * 	 	 	 	 *	Carry out collision detection 
	 * 	 	 	 	 		buildings, vechiles, projectiles and 
	*/
}
void display(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // reset the values
	double aspect = (GLOBAL.WINDOW_MAX_X/(double)GLOBAL.WINDOW_MAX_Y);
	gluPerspective(90,aspect,0.1,1000);
	{
		double temp[3]={
			GLOBAL.CAMERA_POS.x + GLOBAL.CAMERA_LOOK_VECTOR.x,
			GLOBAL.CAMERA_POS.y + GLOBAL.CAMERA_LOOK_VECTOR.y,
			GLOBAL.CAMERA_POS.z + GLOBAL.CAMERA_LOOK_VECTOR.z
		};
		gluLookAt(
				GLOBAL.CAMERA_POS.x,GLOBAL.CAMERA_POS.y,GLOBAL.CAMERA_POS.z,
				temp[0],temp[1],temp[2],
				0,0,1
				);
	}

	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	{ // axies
		glBegin(GL_LINES);
			//X
			glColor3ub(255, 0 , 0 );
			glVertex3d(-50,0,0);
			glVertex3d( 50,0,0);
			//Y
			glColor3ub( 0 ,255, 0 );
			glVertex3d(0,-50,0);
			glVertex3d(0, 50,0);
			//Z
			glColor3ub( 0 , 0 ,255);
			glVertex3d(0,0,-50);
			glVertex3d(0,0, 50);
		glEnd();

		// Label our axies
		glColor3ub(255,255,255);

		glPushMatrix();
		glTranslated(45,0,0);
		glScaled(4.0/104.76,4.0/104.76,4.0/104.76);
		glutStrokeCharacter(GLUT_STROKE_ROMAN,'X');
		glPopMatrix();
		glPushMatrix();
		glTranslated(0,45,0);
		glScaled(4.0/104.76,4.0/104.76,4.0/104.76);
		glutStrokeCharacter(GLUT_STROKE_ROMAN,'Y');
		glPopMatrix();
		glPushMatrix();
		glTranslated(0,0,45);
		glScaled(4.0/104.76,4.0/104.76,4.0/104.76);
		glRotated(90,1,0,0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN,'Z');
		glPopMatrix();
	}
	for(int x=0; x<buildings.size(); x++)
		buildings[x]->draw();

	tank->draw();
	ai_tank->tank->draw();
	for(int i=0; i<projectiles.size();i++){
		projectiles[i]->draw();
	}

	for(int x=0; x<targets.size(); x++)
	    targets[x]->draw();

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
		tankSpeed += 0.15;	
	}else if(key == 'j' || key == 'J'){
		tankBaseRotate += 2;
	}else if(key == 'k' || key == 'K'){
		tankSpeed -= 0.15;
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
	}
	else if(key == 'x' || key == 'X'){
		tank->shoot();
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
		tankSpeed -= 0.15;
	}else if(key == 'j' || key == 'J'){
		tankBaseRotate -= 2;
	}else if(key == 'k' || key == 'K'){
		tankSpeed += 0.15;
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
	}
	else if(key == 'x' || key == 'X'){
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
			targets.push_back(new Target(Point(
					Building::distanceBetweenBuildings*x + Building::distanceBetweenBuildings/2.0,
					Building::distanceBetweenBuildings*y + Building::distanceBetweenBuildings/2.0,
					3)
				));

		}
	}

	tank = new Tank(Point(0, 0, 0));
	ai_tank = new AI_Tank(new Tank(Point(Building::maxBuildingWidth/2.0 + Building::streetWidth/2.0,Building::maxBuildingWidth/2.0 + Building::streetWidth/2.0,0)));


	glutMainLoop();
>>>>>>> 573994be331f7f9baf13127eb9527fbf18a4ef04
	return 0;
}
