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

	return 0;
}
