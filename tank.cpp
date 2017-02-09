#include "globals.h"

void drawTank (void) {
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(tankX, tankY , 0.5);
	glutSolidCube(1);
	glPopMatrix();
}
