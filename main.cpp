#include "globals.h"
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
Skybox * skybox;
Groundbox * groundbox;
bool captureTime = 0;

int oldTime=0.0;
float actualfps, fps=0.0;

int currentTime;
double timeRemaining = TIME_LIMIT;

std::vector<AI_Tank *> ai_tanks;
std::vector<Projectile*> projectiles;

bool youLose()
{
	return ((GLOBAL.gameOver) || (timeRemaining <= 0));
}

void mouseButtons(GLFWwindow* window, int button, int action, int mods){
	if(button==GLFW_MOUSE_BUTTON_LEFT && action==GLFW_PRESS){
		tank->shoot();
	}
}
void mouseMovement(GLFWwindow* window, double x, double y){
	double dx =   x - GLOBAL.prevMouseVirtCoords.x ;
	double dy = ( y - GLOBAL.prevMouseVirtCoords.y ) * -1;
	GLOBAL.prevMouseVirtCoords.x = x;
	GLOBAL.prevMouseVirtCoords.y = y;
	if(!youLose())
	{
		cameraMovement(dx,dy,cameraMode);
	}
}

void gameEngine(){
	if(tank->health == 0)
		GLOBAL.gameOver = true;
	if(!GLOBAL.gameOver)
	{
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
		for(int x=0; x<ai_tanks.size();x++){
			ai_tanks[x]->updateTank();
			ai_tanks[x]->nearbyTarget(tank);
		}

		skybox->update();

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
}

void drawGameOver(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // reset the projection style
	gluOrtho2D(0.0,100.0,100.0,0.0); // simple ortho

	glLineWidth(5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

		int i, len;
		char label[] = "GAME OVER";
		//void *font = GLUT_STROKE_ROMAN;

		glTranslatef(82, 90, 0);
		glScalef(0.5, 0.5, 0.5);

		glPushMatrix();
			glColor3f(1.0,1.0,0.0);
			glRotatef(180.0,1.0,0.0,0.0);
			glScalef(0.105, 0.105, 0.105);
			len = (int) strlen(label);
			glTranslatef(-1530.0, 1575, 0);
			for(i = 0;i<len;i++)
				;//glutStrokeCharacter(font, label[i]);
		glPopMatrix();
		char label2[] = "Nice Try But";
		glPushMatrix();
			glColor3f(0.0,1.0,0.0);
			glRotatef(180.0,1.0,0.0,0.0);
			glScalef(0.105, 0.105, 0.105);
			len = (int) strlen(label2);
			glTranslatef(-1100.0, 1150, 0);
			for(i = 0;i<len;i++)
				;//glutStrokeCharacter(font, label2[i]);
		glPopMatrix();
		char label3[] = "YOU LOST!";
		glPushMatrix();
			glColor3f(0.0,1.0,1.0);
			glRotatef(180.0,1.0,0.0,0.0);
			glScalef(0.105, 0.105, 0.105);
			len = (int) strlen(label3);
			glTranslatef(-755.0, 725, 0);
			for(i = 0;i<len;i++)
				;//glutStrokeCharacter(font, label3[i]);
		glPopMatrix();
		char label4[] = "Your score was: ";
		glPushMatrix();
			glColor3f(1.0,1.0,1.0);
			glRotatef(180.0,1.0,0.0,0.0);
			glScalef(0.08, 0.08, 0.08);
			len = (int) strlen(label4);
			glTranslatef(-1700.0, 400, 0);
			for(i = 0;i<len;i++)
				;//glutStrokeCharacter(font, label4[i]);
			std::ostringstream printNum;
			std::string printy;

			printNum << GLOBAL.score;
			printy = printNum.str();
			len = (int) strlen(&printy[0]);
			for(i = 0;i<len;i++)
				;//glutStrokeCharacter(font,printy[i]);

			printNum.str("");
		glPopMatrix();
		char label5[] = "Press 'q' to exit or 'r' to restart";	
		glPushMatrix();
			glColor3f(1.0,1.0,1.0);
			glRotatef(180.0,1.0,0.0,0.0);
			glScalef(0.06, 0.06, 0.06);
			len = (int) strlen(label5);
			glTranslatef(-2140.0, 300, 0);
			for(i = 0;i<len;i++)
				;//glutStrokeCharacter(font, label5[i]);
		glPopMatrix();

	glPopMatrix();
	glLineWidth(1);
}
void drawTime() {
	glPushMatrix();

		int i, len;
		char label[] = "Time Remaining: ";
		//void *font = GLUT_STROKE_ROMAN;

		glTranslatef(82, 90, 0);
		glScalef(0.15, 0.15, 0.15);

		glPushMatrix();
			glColor3f(1.0,1.0,1.0);
			glRotatef(180.0,1.0,0.0,0.0);
			glScalef(0.125,0.125,0.125);
			glTranslatef(-550.0, 300, 0);
			len = (int) strlen(label);
			for(i = 0;i<len;i++)
				;//glutStrokeCharacter(font, label[i]);

			std::ostringstream printNum;
			std::string printy;
			
			timeRemaining = TIME_LIMIT - difftime(time(0) ,GLOBAL.timeStart);

			printNum << timeRemaining;
			printy = printNum.str();
			len = (int) strlen(&printy[0]);
			for(i = 0;i<len;i++)
				;//glutStrokeCharacter(font,printy[i]);

			printNum.str("");
		glPopMatrix();
	glPopMatrix();
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
	drawTime();

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
		
		gluLookAt(
				GLOBAL.CAMERA_POS.x,GLOBAL.CAMERA_POS.y,GLOBAL.CAMERA_POS.z,
				temp[0],temp[1],temp[2],
				0,0,1
				);
	}
	}
	
	else{
		// Herron: sets orthographic view
		glOrtho( 500.0, -500.0, 500.0, -500.0, 0.1, 1000);
		gluLookAt(450.0, 450.0, 800.0, 450.0 , 450.0, 0.0, 0.0, -1.0, -1.0);
	}

	
	glMatrixMode(GL_MODELVIEW);

	if(!orthoView){
		for(int x=0; x<buildings.size(); x++)
			buildings[x]->draw();
		for(int x=0; x<targets.size(); x++)
		    targets[x]->draw();
	}else{
		for(int x=0; x<buildings.size(); x++)
			buildings[x]->draw_simple();
		for(int x=0; x<targets.size(); x++)
			targets[x]->draw_map_marker();
	}

	tank->draw();
	for(int x=0; x<ai_tanks.size();x++)
		ai_tanks[x]->tank->draw();

	for(int i=0; i<projectiles.size();i++){
		projectiles[i]->draw();
	}


	skybox->draw();
	groundbox->draw();
	//tank->drawHealthBar(tank->health);
}

void drawBoundingBoxes(){
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
		
		gluLookAt(
				GLOBAL.CAMERA_POS.x,GLOBAL.CAMERA_POS.y,GLOBAL.CAMERA_POS.z,
				temp[0],temp[1],temp[2],
				0,0,1
				);
	}
	}
	
	else{
		glOrtho(-500.0, 500.0, -500.0, 500.0, 0.1, 1000);{
			gluLookAt(450.0, 450.0, 800.0, 450.0 , 450.0, 0.0, 0.0, -1.0, -1.0);
		}
	}

	
	glMatrixMode(GL_MODELVIEW);

	// for(int x=0; x<buildings.size(); x++)
	// 	buildings[x]->draw();

	// tank->draw();
	// ai_tank->tank->draw();

	// for(int i=0; i<projectiles.size();i++){
	// 	projectiles[i]->draw();
	// }

	for(int x=0; x<targets.size(); x++){
	    auto box = targets[x]->getBoundingBox();
	    for(int y=0; y<box.size(); y++){
	    	box[y].drawLines();
	    }
	}

	{
	    auto box = tank->getBoundingBox();
	    for(int y=0; y<box.size(); y++){
	    	box[y].setColor(255,255,255);
	    	box[y].drawLines();
	    }
	}
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
		buildings[x]->draw_simple();
	for(int x=0; x<targets.size(); x++)
		targets[x]->draw_map_marker();

	tank->draw();
	for(int x=0; x<ai_tanks.size();x++)
		ai_tanks[x]->tank->draw();
}
void display(){

	//remove this clear for game over cast over moment of failure
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,GLOBAL.WINDOW_MAX_X,GLOBAL.WINDOW_MAX_Y);

	if(!youLose()) {
		if(!orthoView)glEnable(GL_LIGHTING);
		updateLights();

		drawWorld();
		collisionTest();
	
		//===============================================================================
		glDisable(GL_LIGHTING);

		glClear(GL_DEPTH_BUFFER_BIT);
		drawHud();

		glClear(GL_DEPTH_BUFFER_BIT);
		glViewport(0,0,GLOBAL.WINDOW_MAX_X/4,GLOBAL.WINDOW_MAX_Y/4);
		if(!orthoView)drawMinimap();
	}
	else {
		glDisable(GL_LIGHTING);
		drawGameOver();
	}

	glFlush();
}



void keyboardButtons(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (action == GLFW_REPEAT)
		return;
	int buttonReverse = (action==GLFW_RELEASE ? -1 : 1) ;
	//printf("%c(%d) %d %d 0x%x\n",key,key,scancode,action,mods);
	switch(key){
		case GLFW_KEY_Q:
			GLOBAL.gameExitRequest = true;
			break;

		case GLFW_KEY_W:
			if(cameraMode==0)camMove_forward += camMove_speed * buttonReverse;
			else tankAccel += 0.005 * buttonReverse;
			break;
		case GLFW_KEY_S:
			if(cameraMode==0)camMove_forward -= camMove_speed * buttonReverse;
			else tankAccel -= 0.005 * buttonReverse;
			break;
		case GLFW_KEY_A:
			if(cameraMode==0)camMove_strafe += camMove_speed * buttonReverse;
			else tankBaseRotate += 2 * buttonReverse;
			break;
		case GLFW_KEY_D:
			if(cameraMode==0)camMove_strafe -= camMove_speed * buttonReverse;
			else tankBaseRotate -= 2 * buttonReverse;
			break;
		case GLFW_KEY_C:
			camMove_vert += camMove_speed * buttonReverse;
			break;
		case GLFW_KEY_SPACE:
			camMove_vert -= camMove_speed * buttonReverse;
			break;

		case GLFW_KEY_X:
			if(action == GLFW_RELEASE) break;
			tank->shoot();
			break;

		case GLFW_KEY_8:
			if(action == GLFW_RELEASE) break;
			tank->laser = !tank->laser;
			break;

		case GLFW_KEY_Z:
			if(action == GLFW_RELEASE) break;
			if(cameraMode>=2) //currently looking at three camera modes that we switch between
				cameraMode = 0;
			else
				cameraMode++;
			break;
		case GLFW_KEY_V:
			if(action == GLFW_RELEASE) break;
			orthoView = !orthoView;
			break;
		case GLFW_KEY_R:
			if(action == GLFW_RELEASE) break;
			if(GLOBAL.gameOver)//when game over, r to restart game
			{
				delete tank;
				for(int x=ai_tanks.size()-1; x>=0; x--){
					delete ai_tanks[x];
					ai_tanks.pop_back();
				}
				

				tank = new Tank(Point(0, Building::maxBuildingWidth/2.0 + Building::streetWidth/2.0, 0));
				for(int x=0; x<NUM_AI_TANKS; x++){
					int dx = rand()%NUM_BLOCKS_WIDE * Building::distanceBetweenBuildings;
					int dy = rand()%NUM_BLOCKS_WIDE * Building::distanceBetweenBuildings;
					AI_Tank * ai_tank = new AI_Tank(new Tank(
						Point(Building::maxBuildingWidth/2.0 + Building::streetWidth/2.0 + dx,
							Building::maxBuildingWidth/2.0 + Building::streetWidth/2.0 + dy,
							0)
						));
					ai_tanks.push_back(ai_tank);
				}
				GLOBAL.reset();
			}
			break;
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

int main(int argc,char** args){
	if(argc > 1)
		captureTime=1;	

	if(!glfwInit()){
		printf("Unable to start glfw\n");
		exit(-1);
	}
	GLOBAL.windowHandle = glfwCreateWindow(GLOBAL.WINDOW_MAX_X, GLOBAL.WINDOW_MAX_Y, "Pendulum", NULL, NULL);
	if ( !GLOBAL.windowHandle ){
		glfwTerminate();
		printf("Unable to make a window\n");
		exit(-1);
	}
	/* Make the GL context for the window the current context that we will draw with */
	glfwMakeContextCurrent(GLOBAL.windowHandle);

	glfwSetFramebufferSizeCallback(GLOBAL.windowHandle, windowResize);
	glfwSetKeyCallback(GLOBAL.windowHandle, keyboardButtons);
	glfwSetInputMode(GLOBAL.windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(GLOBAL.windowHandle, mouseMovement);
	glfwSetMouseButtonCallback(GLOBAL.windowHandle, mouseButtons);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(GLOBAL.windowHandle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	glClearColor(0,0,0,0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE); // make the lighting track the color of objects

	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );

	//let people use random numbers without worrying about how to seed things
	srand(time(NULL));

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
				Target *tDawg = new Target(Point(	
					Building::distanceBetweenBuildings*x,
					Building::distanceBetweenBuildings*y + (Building::maxBuildingWidth)/2.0 + 0.55,
					targetCenter));
				(*tDawg).setRotation(180.0);
				targets.push_back(tDawg);	
			} else if(randSide == 3) {//"east"
				Target *tDawg = new Target(Point(
					Building::distanceBetweenBuildings*x - (Building::maxBuildingWidth)/2.0 - 0.55,
					Building::distanceBetweenBuildings*y - (Building::maxBuildingWidth)/32.0,
					targetCenter));
				(*tDawg).setRotation(-90.0);
				targets.push_back(tDawg);
			} else {
				std::cout << "SOMETHING HAS GONE HORRIBLY WRONG" << std::endl;
				goto main_exit_cleanup;
			}
		}
	}

	tank = new Tank(Point(0, Building::maxBuildingWidth/2.0 + Building::streetWidth/2.0, 0));
	for(int x=0; x<NUM_AI_TANKS; x++){
		int dx = rand()%NUM_BLOCKS_WIDE * Building::distanceBetweenBuildings;
		int dy = rand()%NUM_BLOCKS_WIDE * Building::distanceBetweenBuildings;
		AI_Tank * ai_tank = new AI_Tank(new Tank(
			Point(Building::maxBuildingWidth/2.0 + Building::streetWidth/2.0 + dx,
				Building::maxBuildingWidth/2.0 + Building::streetWidth/2.0 + dy,
				0)
			));
		ai_tanks.push_back(ai_tank);
	}

	//oldTime = glutGet(GLUT_ELAPSED_TIME);

	skybox = new Skybox();
	groundbox = new Groundbox(Building::maxBuildingWidth, Building::streetWidth, Building:: sidewalkWidth);

	while (!glfwWindowShouldClose(GLOBAL.windowHandle) && !GLOBAL.gameExitRequest){
		gameEngine();
		display();
		glfwSwapBuffers(GLOBAL.windowHandle);
		glfwPollEvents();
	}

main_exit_cleanup:
	glfwTerminate();
	return 0;
}
