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


AI_Tank * ai_tank;
AI_Tank * ai_tank2;
AI_Tank * ai_tank3;
AI_Tank * ai_tank4;
AI_Tank * ai_tank5;

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
	tank->update(tankBaseRotate, tankTurretRotate, tankCannonRotate, cameraMode, tankAccel); // the things below need to be moved into this function
	ai_tank->updateTank(tank);
	ai_tank->nearbyTarget(tank);
	
	ai_tank2->updateTank(tank);
	ai_tank2->nearbyTarget(tank);

	ai_tank3->updateTank(tank);
        ai_tank3->nearbyTarget(tank);

	ai_tank4->updateTank(tank);
        ai_tank4->nearbyTarget(tank);

	ai_tank5->updateTank(tank);
        ai_tank5->nearbyTarget(tank);


	for(int i=0; i < projectiles.size(); i++){
		projectiles[i]->update();
	}

}

void drawHud()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // reset the projection style
	gluOrtho2D(0.0,100.0,100.0,0.0); // simple ortho

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	tank->drawHealthBar();
	tank->drawCooldownBar();
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
			gluLookAt(450.0, 450.0, -800.0, 450.0 , 450.0, 0.0, 0.0, -1.0, -1.0);
		}
	}

	
	glMatrixMode(GL_MODELVIEW);

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
	ai_tank2->tank->draw();
	ai_tank3->tank->draw();
        ai_tank4->tank->draw();
	ai_tank5->tank->draw();

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
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,GLOBAL.WINDOW_MAX_X,GLOBAL.WINDOW_MAX_Y);
	drawWorld();
	
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

	//let people use random numbers without worrying about how to seed things
	srand(time(NULL));

	std::cout << "fire " << std::endl;

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
	std::cout << "fire " << std::endl;
	ai_tank = new AI_Tank(new Tank(Point(30, 31, 0)), tank);//60, 60,0)), tank);//Point(Building::maxBuildingWidth/2.0 + Building::streetWidth/2.0,Building::maxBuildingWidth/2.0 + Building::streetWidth/2.0,0)));
	std::cout << "fire " << std::endl;
	
	// second ai tank
	ai_tank2 = new AI_Tank(new Tank(Point(90, 90, 0)), tank);
	ai_tank3 = new AI_Tank(new Tank(Point(150, 150, 0)), tank);
	ai_tank4 = new AI_Tank(new Tank(Point(210,210, 0)), tank);
	ai_tank5 = new AI_Tank(new Tank(Point(270, 270, 0)), tank);



	glutMainLoop();

	return 0;
}
