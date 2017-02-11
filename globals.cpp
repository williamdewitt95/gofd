#include "globals.h"

GLOBAL_SETTINGS::GLOBAL_SETTINGS(){
	WINDOW_MAX_X = 1000;
	WINDOW_MAX_Y = 1000;

	WORLD_COORDINATE_MIN_X = 0.0;
	WORLD_COORDINATE_MAX_X = 1000.0;
	WORLD_COORDINATE_MIN_Y = 0.0;
	WORLD_COORDINATE_MAX_Y = 1000.0;

	CAMERA_POS = {0,-2,0};
	CAMERA_LOOK_VECTOR = {0,1,0};
	CAMERA_ANGLE_VERTICAL = 0;
	CAMERA_ANGLE_HORIZONTAL = 90;
}

GLOBAL_SETTINGS GLOBAL;

void loadTex(std::string name){
	if(GLOBAL.TEXTURES_LOADED.count(name) != 0){
		return; //the texture has already been loaded
	}
	struct TextureInfo ti;
	ti.name = name;

	bool wrap = true;
	Image im(name);
	ti.width = im.width();
	ti.height = im.height();

	glGenTextures(1,(GLuint*)&ti.textureRef); // create the texture space
	glBindTexture(GL_TEXTURE_2D,ti.textureRef);
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); // make the color of the polygons and the lighting affect the image

	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
	// when texture area is large, bilinear filter the first mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// if wrap is true, the texture wraps over at the edges (repeat)
	// false, the texture ends at the edges (clamp)
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );

	//time to finnally put in our pixel data
	gluBuild2DMipmaps(GL_TEXTURE_2D,4,im.width(),im.height(),GL_RGBA,GL_UNSIGNED_BYTE,&im[0][0]);

	GLOBAL.TEXTURES_LOADED[name]=ti;
	glBindTexture(GL_TEXTURE_2D,0); // reset to the basic texture again
}

void windowResize(int width, int height){

	//move the world cordinates to match the change in the windows draw area
	GLOBAL.WORLD_COORDINATE_MIN_X += 0;
	GLOBAL.WORLD_COORDINATE_MAX_X += width - GLOBAL.WINDOW_MAX_X;
	GLOBAL.WORLD_COORDINATE_MIN_Y += 0;
	GLOBAL.WORLD_COORDINATE_MAX_Y += height - GLOBAL.WINDOW_MAX_Y;

	//remember what the new size of the window is
	GLOBAL.WINDOW_MAX_X = width;
	GLOBAL.WINDOW_MAX_Y = height;

	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();
	// gluOrtho2D(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X,  // do the scale again
	//           WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);

	//make the scene visable over the whole window
	glViewport(0,0,width,height);
	glutPostRedisplay();
}
void scaleMouse(int &x, int &y){
	y=GLOBAL.WINDOW_MAX_Y-y;

	y*=(GLOBAL.WORLD_COORDINATE_MAX_Y - GLOBAL.WORLD_COORDINATE_MIN_Y) / ((double)GLOBAL.WINDOW_MAX_Y);
	x*=(GLOBAL.WORLD_COORDINATE_MAX_X - GLOBAL.WORLD_COORDINATE_MIN_X) / ((double)GLOBAL.WINDOW_MAX_X);

	y+=GLOBAL.WORLD_COORDINATE_MIN_Y;
	x+=GLOBAL.WORLD_COORDINATE_MIN_X;
}
void FPS_CameraMovement(int x, int y, double center_x,double  center_y, double center_z){
	double movementDivisor = 3.0;
	//x and y are window cordinates
	//it is up to us to get deltas
	y=GLOBAL.WINDOW_MAX_Y-y;
	int midX = GLOBAL.WINDOW_MAX_X/2;
	int midY = GLOBAL.WINDOW_MAX_Y/2;

	int dx = x-midX;
	int dy = y-midY;
	

	double &angleH = GLOBAL.CAMERA_ANGLE_HORIZONTAL;
	double &angleV = GLOBAL.CAMERA_ANGLE_VERTICAL;
	angleH += dx/movementDivisor;
	if(angleH>360)angleH-=360;
	if(angleH<0)angleH+=360;
	angleV += dy/movementDivisor;
	if(angleV>90)angleV=90;
	if(angleV<-90)angleV=-90;

	// we will have a length of 5 for the line in the XY plane
	// GLOBAL.CAMERA_LOOK_VECTOR.x = 5 * ( cos(angleH*PI/180.0));
	// GLOBAL.CAMERA_LOOK_VECTOR.y = 5 * (-sin(angleH*PI/180.0));
	// make the z from pathagarean formula - our angle is measured from the horizontal plane
	// GLOBAL.CAMERA_LOOK_VECTOR.z = 5 * tan(angleV*PI/180.0);
	// GLOBAL.CAMERA_POS.z = 0;



	GLOBAL.CAMERA_POS.x = center_x + 4*cos(angleH*PI/180.0);
	GLOBAL.CAMERA_POS.y = center_y + 4*-sin(angleH*PI/180.0);

	// GLOBAL.CAMERA_POS.z = center_z + sin(angleV*PI/180.0)+2;
GLOBAL.CAMERA_POS.z=2;
	GLOBAL.CAMERA_LOOK_VECTOR.x = center_x - GLOBAL.CAMERA_POS.x;
	GLOBAL.CAMERA_LOOK_VECTOR.y = center_y - GLOBAL.CAMERA_POS.y;
	GLOBAL.CAMERA_LOOK_VECTOR.z = center_z - GLOBAL.CAMERA_POS.z;

	if(dx==0 && dy==0)
		return; //we are not really doing anything, so we will simply ignore this thing

	// printf("PassiveFunc\t%dx%d\n",dx,dy); // pixel deltas
	// printf("angles\t%f %f\n",angleH,angleV); // look angles
	// printf("CAMERA_LOOK_VECTOR\t%.2f %.2f %.2f\n",GLOBAL.CAMERA_LOOK_VECTOR.x,GLOBAL.CAMERA_LOOK_VECTOR.y,GLOBAL.CAMERA_LOOK_VECTOR.z); // look vector
	// printf("CAMERA_POS\t%.2f %.2f %.2f\n",GLOBAL.CAMERA_POS.x,GLOBAL.CAMERA_POS.y,GLOBAL.CAMERA_POS.z); // position 

	glutWarpPointer(midX,GLOBAL.WINDOW_MAX_Y-midY);
}
