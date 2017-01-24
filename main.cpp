#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>

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
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_MAX_X,WINDOW_MAX_Y);
    glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
    glutCreateWindow("Game of Drones");

}

void init(){

        glClearColor ( 1.0, 1.0, 1.0, 0.0);

        glMatrixMode(GL_PROJECTION);
        gluOrtho2D(WORLD_COORD_MIN_X, WORLD_COORD_MAX_X,
                   WORLD_COORD_MIN_Y, WORLD_COORD_MAX_Y);

        glMatrixMode(GL_MODELVIEW);

}

void display(){

}

void mouse(){

}

void keyboard(){

}

void main(int argc, char** argv){

        myGlutInit(argc,argv);
        init();

        glutMouseFunc(mouse);
        glutKeyboardFunc(keyboard);
        glutDisplayFunc(display);
        glutMainLoop();


}
