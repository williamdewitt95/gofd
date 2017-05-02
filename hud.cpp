

#include "hud.h"
//all hud draw functions are approximately the same
void drawScore(){
	//push matrix so we don't contaminate matrix we were working in with transformations
	glPushMatrix();
		
		int i, len;
		//char array to print to screen
		char label[] = "Score: ";
		//font used when printing
		void *font = GLUT_STROKE_ROMAN;
		//transformations that looked ok; no particular meaning behind numbers
		glTranslatef(82, 90, 0);
		glScalef(0.15, 0.15, 0.15);
		
		glPushMatrix();
			glColor3f(1.0,1.0,1.0);
			glRotatef(180.0,1.0,0.0,0.0);
			glScalef(0.125,0.125,0.125);
			glTranslatef(-550.0, 100, 0);
			//store number of characters to print
			len = (int) strlen(label);
			//print every char in label using that font
			for(i = 0;i<len;i++)
				glutStrokeCharacter(font, label[i]);
			//use an ostringstream to turn number into string and print
			std::ostringstream printNum;
			std::string printy;
			//put score int into stream
			printNum << GLOBAL.score;
			//return stream contents as string
			printy = printNum.str();
			//store number of chars to print and print them
			len = (int) strlen(&printy[0]);
			for(i = 0;i<len;i++)
				glutStrokeCharacter(font,printy[i]);

			printNum.str("");
		glPopMatrix();
	glPopMatrix();
}

//tank object contains cooldown value so we pass it as parameter
void drawCooldownBar(Tank tank){
	glPushMatrix();

	int i, len;
	char label[] = "Cooldown";
	void *font = GLUT_STROKE_ROMAN;

	glTranslatef(82, 90, 0);
	glScalef(0.15, 0.15, 0.15);

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glRotatef(180.0,1.0,0.0,0.0);
	glScalef(0.125,0.125,0.125);
	glTranslatef(-550.0, -100, 0);
	len = (int) strlen(label);
	for(i = 0;i<len;i++)
		glutStrokeCharacter(font, label[i]);

	glPopMatrix();
	
	glBegin(GL_POLYGON);
		//draw remaining cooldown time as rectangle; as cooldown decreases, gives appearance of progress bar decreasing
		//actually 2 separate rectangles whose sizes are inversely proportional to one another ;)
		glColor3ub(255,255,255);
		glVertex2f(0.0,0.0);
		glVertex2f(0.0,20.0);
		glVertex2f((float) (tank.cooldown/100.0)*100.0, 20.0);
		glVertex2f((float) (tank.cooldown/100.0)*100.0,  0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
		
		//draw missing cooldown time as rectangle that connects to above rectangle
		glColor3ub(0,0,200);
		glVertex2f((float) (tank.cooldown/100.0)*100.0,  0.0);
		glVertex2f((float) (tank.cooldown/100.0)*100.0, 20.0);
		glVertex2f(100.0,20.0);
		glVertex2f(100.0,0.0);
	glEnd();

	glPopMatrix();
}
//just like drawCooldown
void drawHealthBar(Tank tank){
	glPushMatrix();

		int i, len;
		char healthLabel[] = "Health";
		void *font = GLUT_STROKE_ROMAN;

		glTranslatef(82, 95, 0);
		glScalef(0.15, 0.15, 0.15);

		glPushMatrix();
			glColor3f(1.0,1.0,1.0);
			glRotatef(180.0,1.0,0.0,0.0);
			glScalef(0.125,0.125,0.125);
			glTranslatef(-400, -130, 0);
			len = (int) strlen(healthLabel);
			for(i = 0;i<len;i++)
				glutStrokeCharacter(font, healthLabel[i]);

		glPopMatrix();
		
		glBegin(GL_POLYGON);
			//draw remaining health
			glColor3ub(0,255,0);
			glVertex2f(0.0,0.0);
			glVertex2f(0.0,20.0);
			glVertex2f((float) (tank.health/100.0)*100.0, 20.0);
			glVertex2f((float) (tank.health/100.0)*100.0,  0.0);
		glEnd();
		
		glBegin(GL_POLYGON);
			
			//draw missing heath bar
			glColor3ub(255,0,0);
			glVertex2f((float) (tank.health/100.0)*100.0,  0.0);
			glVertex2f((float) (tank.health/100.0)*100.0, 20.0);
			glVertex2f(100.0,20.0);
			glVertex2f(100.0,0.0);
		glEnd();

	glPopMatrix();
}



void showFPS(float &fps, int &oldTime, float &actualfps) {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    char str_fps[15];
    if ( (currentTime - oldTime) > 1000 ){
        actualfps = fps;
        fps = 0.0;
        oldTime = currentTime;
    } else
        fps++;
    sprintf(&str_fps[0], "FPS = %.0f",actualfps);


    glPushMatrix();
    glClear(GL_DEPTH_BUFFER_BIT);

    void *font = GLUT_STROKE_ROMAN;
    glColor3f(1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // reset the projection style
    gluOrtho2D(0.0,100.0,100.0,0.0); // simple ortho

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(01, 03, 0);
    glScalef(0.15, 0.15, 0.15);

    glRotatef(180.0, 1.0, 0.0, 0.0);
    glScalef(0.055,0.055,0.055);
    int len = (int) strlen(str_fps);
    for (int i = 0; i < len; i++) {
        glutStrokeCharacter(font, str_fps[i]);
    }
    glPopMatrix();
}




