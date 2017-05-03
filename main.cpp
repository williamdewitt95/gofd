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
bool youLose()
{
	return ((GLOBAL.gameOver) || (timeRemaining <= 0));
}
void passiveMouseMovement(int x,int y){
	//x and y are window cordinates
	//it is up to us to get deltas
	if(!youLose())
	{
		cameraMovement(x,y,tank->center,cameraMode);
		tank->turretFollowMouse(x, y,cameraMode);
	}
}
void mouseMovement(int x,int y){
	//x and y are window cordinates
	//it is up to us to get deltas
	// FPS_CameraMovement(x,y);
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
		void *font = GLUT_STROKE_ROMAN;

		glTranslatef(82, 90, 0);
		glScalef(0.5, 0.5, 0.5);

		glPushMatrix();
			glColor3f(1.0,1.0,0.0);
			glRotatef(180.0,1.0,0.0,0.0);
			glScalef(0.105, 0.105, 0.105);
			len = (int) strlen(label);
			glTranslatef(-1530.0, 1575, 0);
			for(i = 0;i<len;i++)
				glutStrokeCharacter(font, label[i]);
		glPopMatrix();
		char label2[] = "Nice Try But";
		glPushMatrix();
			glColor3f(0.0,1.0,0.0);
			glRotatef(180.0,1.0,0.0,0.0);
			glScalef(0.105, 0.105, 0.105);
			len = (int) strlen(label2);
			glTranslatef(-1100.0, 1150, 0);
			for(i = 0;i<len;i++)
				glutStrokeCharacter(font, label2[i]);
		glPopMatrix();
		char label3[] = "YOU LOST!";
		glPushMatrix();
			glColor3f(0.0,1.0,1.0);
			glRotatef(180.0,1.0,0.0,0.0);
			glScalef(0.105, 0.105, 0.105);
			len = (int) strlen(label3);
			glTranslatef(-755.0, 725, 0);
			for(i = 0;i<len;i++)
				glutStrokeCharacter(font, label3[i]);
		glPopMatrix();
		char label4[] = "Your score was: ";
		glPushMatrix();
			glColor3f(1.0,1.0,1.0);
			glRotatef(180.0,1.0,0.0,0.0);
			glScalef(0.08, 0.08, 0.08);
			len = (int) strlen(label4);
			glTranslatef(-1700.0, 400, 0);
			for(i = 0;i<len;i++)
				glutStrokeCharacter(font, label4[i]);
			std::ostringstream printNum;
			std::string printy;

			printNum << GLOBAL.score;
			printy = printNum.str();
			len = (int) strlen(&printy[0]);
			for(i = 0;i<len;i++)
				glutStrokeCharacter(font,printy[i]);

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
				glutStrokeCharacter(font, label5[i]);
		glPopMatrix();

	glPopMatrix();
	glLineWidth(1);
}
void drawTime() {
	glPushMatrix();

		int i, len;
		char label[] = "Time Remaining: ";
		void *font = GLUT_STROKE_ROMAN;

		glTranslatef(82, 90, 0);
		glScalef(0.15, 0.15, 0.15);

		glPushMatrix();
			glColor3f(1.0,1.0,1.0);
			glRotatef(180.0,1.0,0.0,0.0);
			glScalef(0.125,0.125,0.125);
			glTranslatef(-550.0, 300, 0);
			len = (int) strlen(label);
			for(i = 0;i<len;i++)
				glutStrokeCharacter(font, label[i]);

			std::ostringstream printNum;
			std::string printy;
			
			timeRemaining = TIME_LIMIT - difftime(time(0) ,GLOBAL.timeStart);

			printNum << timeRemaining;
			printy = printNum.str();
			len = (int) strlen(&printy[0]);
			for(i = 0;i<len;i++)
				glutStrokeCharacter(font,printy[i]);

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
	glutSwapBuffers();

	if(captureTime == 1)
	{
		screencapture(GLOBAL.step); 
		GLOBAL.step++;
	} 

	glutPostRedisplay(); //always say we want a redraws
}

void keyboardButtons(unsigned char key, int x, int y){
	if(key == 'q' || key == 'Q'){
		exit(0);
	}else if(key == 'w' || key == 'W'){
		if(cameraMode==0)camMove_forward += camMove_speed;
		else tankAccel += 0.005;
	}else if(key == 's' || key == 'S'){
		if(cameraMode==0)camMove_forward -= camMove_speed;
		else tankAccel -= 0.005;
	}else if(key == 'a' || key == 'A'){
		if(cameraMode==0)camMove_strafe += camMove_speed;
		else tankBaseRotate += 2;
	}else if(key == 'd' || key == 'D'){
		if(cameraMode==0)camMove_strafe -= camMove_speed;
		else tankBaseRotate -= 2;


	}else if(key == 'n' || key == 'N'){
		tankScale -= 0.05;
	}else if(key == 'm' || key == 'M'){
		tankScale += 0.05;
	}else if(key == 'z' || key == 'Z'){
		if(cameraMode>=2){//currently looking at three camera modes that we switch between
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
		//glutPostRedisplay();
		//printf("%d\n", tank->health);
	}else if(key == 'v' || key == 'V' ){
		// Herron: sets to top down orthographic view
		orthoView = !orthoView;
	}else if(key == 'r' || key == 'R'){
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
	}else{
//		printf("Unknown Key Down %d\n",key); 
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
		if(cameraMode==0)camMove_forward -= camMove_speed;
		else tankAccel -= 0.005;
	}else if(key == 's' || key == 'S'){
		if(cameraMode==0) camMove_forward += camMove_speed;
		else tankAccel += 0.005;
	}else if(key == 'a' || key == 'A'){
		if(cameraMode==0) camMove_strafe -= camMove_speed;
		else tankBaseRotate -= 2;
	}else if(key == 'd' || key == 'D'){
		if(cameraMode==0) camMove_strafe += camMove_speed;
		else tankBaseRotate += 2;
	
	}else if(key == 'n' || key == 'N'){
	}else if(key == 'm' || key == 'M'){
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
	//	printf("Unknown Key Up %d\n",key); This is kind of annoying
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
void joystickControls(unsigned int buttonMask, int x, int y, int z)
{
	//This was for figuring out all the buttonmasks and stuff from the joystick control.	
	/*unsigned int a = buttonMask;
	for(int i = 0; i < 32; i++)
	{
		printf("%d", a & 1);
		a >>=1;
	}
	printf(" %d %d %d \n", x, y, z);*/
	
	//Mapped to fire button, and mapped to trigger for pointer finger. Bitshifting and bitwise and.
	if( buttonMask & 1 || (buttonMask >> 1) & 1)
		tank->shoot();

	//Left hand pointer finger controls base movement.
	if((buttonMask >> 20) & 1)
	{
		tankBaseRotate = -2;
	}
	else if((buttonMask >> 22) & 1)
	{
		tankBaseRotate = 2;
	}
	else
	{
		tankBaseRotate = 0;
	}

	//It was really easy go up to 200, so I set a large deadzone for staying at zero. Technically, at exactly 200, nothing happens.
	if(abs(z) < 200)
	{
		tankAccel = 0;
	}
	else if(z < 200)
	{
		tankAccel = 0.005;
	}
	else if(z > -200)
	{
		tankAccel = -0.005;
	}

	//We want to check if either are above, otherwise it locks controls to just on coordinate and not the other.
	if(abs(x) > 50 || abs(y) > 50)
	{
		//Fun ternary stayements to check and set the delta x or y values.
		int xMove = abs(x) > 50 ? (x > 0 ? 2:-2) : 0;
		int yMove = abs(y) > 50 ? (y > 0 ? -2:2) : 0;

		//We're pretending to be the mouse here. Where as we would read from the mouse and move the camera
		//we instead pretend the mouse has moved by added our x and y movements to the center, where the mouse
		//ordinarily would be. This makes it seem as though the mouse moved, when its just the joystick.
		cameraMovement(GLOBAL.WINDOW_MAX_X/2 + xMove, GLOBAL.WINDOW_MAX_Y/2 + yMove,tank->center,cameraMode);
		tank->turretFollowMouse(GLOBAL.WINDOW_MAX_X/2 + xMove, GLOBAL.WINDOW_MAX_Y/2 + yMove,cameraMode);
	}
}

int main(int argc,char** args){
	if(argc > 1)
		captureTime=1;	

	glutInit(&argc, args);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA | GLUT_ALPHA);

	glutInitWindowPosition(0,0);
	glutInitWindowSize(GLOBAL.WINDOW_MAX_X,GLOBAL.WINDOW_MAX_Y);
	glutCreateWindow("Pendulum");

	glClearColor(0,0,0,0);

	GLOBAL.step=0;

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
	glutJoystickFunc(joystickControls, 1);
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
				exit(0);
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


	oldTime = glutGet(GLUT_ELAPSED_TIME);

	skybox = new Skybox();
	groundbox = new Groundbox(Building::maxBuildingWidth, Building::streetWidth, Building:: sidewalkWidth);

	glutMainLoop();
	return 0;
}
