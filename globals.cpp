#include "globals.h"
#include "building.h"

GLOBAL_SETTINGS::GLOBAL_SETTINGS(){
	WINDOW_MAX_X = 1000;
	WINDOW_MAX_Y = 1000;

	WORLD_COORDINATE_MIN_X = 0.0;
	WORLD_COORDINATE_MAX_X = 1000.0;
	WORLD_COORDINATE_MIN_Y = 0.0;
	WORLD_COORDINATE_MAX_Y = 1000.0;

	CAMERA_POS = {Building::distanceBetweenBuildings/2.0,
	              Building::distanceBetweenBuildings/2.0,
	              2
			};
	CAMERA_LOOK_VECTOR = {0,1,0};
	CAMERA_ANGLE_VERTICAL = 0;
	CAMERA_ANGLE_HORIZONTAL = 90;

	LIGHTS[0].possition[0]=0;
	LIGHTS[0].possition[1]=0;
	LIGHTS[0].possition[2]=0;
	LIGHTS[0].attenuation_linear=1.0;
	LIGHTS[0].attenuation_quadratic=1.0;
	LIGHTS[0].color_ambient[0]=1.0;
	LIGHTS[0].color_ambient[1]=1.0;
	LIGHTS[0].color_ambient[2]=1.0;
	LIGHTS[0].color_ambient[3]=1.0;
}

GLOBAL_SETTINGS GLOBAL;

void loadTex(std::string name){
	if(GLOBAL.TEXTURES_LOADED.count(name) != 0){
		return; //the texture has already been loaded
	}
	struct TextureInfo ti;
	ti.name = name;

	unsigned char * data;

	bool wrap = true;
	// Image im(name);
	// ti.width = im.width();
	// ti.height = im.height();

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

	//pull the actual image data from the texture
	data = SOIL_load_image(ti.name.c_str(), &ti.width, &ti.height, 0, SOIL_LOAD_RGBA);

	//time to finnally put in our pixel data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ti.width, ti.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	gluBuild2DMipmaps(GL_TEXTURE_2D,4,ti.width,ti.height,GL_RGBA,GL_UNSIGNED_BYTE,data);

	GLOBAL.TEXTURES_LOADED[name]=ti;
	glBindTexture(GL_TEXTURE_2D,0); // reset to the basic texture again
    SOIL_free_image_data(data);

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

void cameraMovement(int x, int y, Point center, int cameraMode){
	switch(cameraMode){
		case 0:
			free_CameraMovement(x,y);
			break;
		case 1:
			FPS_CameraMovement(x,y,center);

			break;
		case 2:
			thirdPerson_CameraMovement(x,y,center);
			break;
		case 3: 
			break;
	}
	
}
void FPS_CameraMovement(int x, int y, Point center){//first person is actually sitting on top of turret
	// bool firstPerson = false;//for rapid testing of different cameras
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
		GLOBAL.CAMERA_LOOK_VECTOR.x = 5 * ( cos(angleH*PI/180.0));
		GLOBAL.CAMERA_LOOK_VECTOR.y = 5 * (-sin(angleH*PI/180.0));
		// make the z from pathagarean formula - our angle is measured from the horizontal plane
		GLOBAL.CAMERA_LOOK_VECTOR.z = 5 * tan(angleV*PI/180.0);
		// GLOBAL.CAMERA_POS.z = 0;

		GLOBAL.CAMERA_POS.x = center.x;
		GLOBAL.CAMERA_POS.y = center.y;



	// 
	// GLOBAL.CAMERA_POS.z = center_z + sin(angleV*PI/180.0)+2;
	GLOBAL.CAMERA_POS.z=2;



	// GLOBAL.CAMERA_LOOK_VECTOR.z = 0;

	if(dx==0 && dy==0)
		return; //we are not really doing anything, so we will simply ignore this thing

	// printf("PassiveFunc\t%dx%d\n",dx,dy); // pixel deltas
	// printf("angles\t%f %f\n",angleH,angleV); // look angles
	// printf("CAMERA_LOOK_VECTOR\t%.2f %.2f %.2f\n",GLOBAL.CAMERA_LOOK_VECTOR.x,GLOBAL.CAMERA_LOOK_VECTOR.y,GLOBAL.CAMERA_LOOK_VECTOR.z); // look vector
	// printf("CAMERA_POS\t%.2f %.2f %.2f\n",GLOBAL.CAMERA_POS.x,GLOBAL.CAMERA_POS.y,GLOBAL.CAMERA_POS.z); // position 

	glutWarpPointer(midX,GLOBAL.WINDOW_MAX_Y-midY);
}

void free_CameraMovement(int x, int y){//move the camera around not bound to the tank
	double movementDivisor = 6.0;
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
	GLOBAL.CAMERA_LOOK_VECTOR.x = 5 * ( cos(angleH*PI/180.0));
	GLOBAL.CAMERA_LOOK_VECTOR.y = 5 * (-sin(angleH*PI/180.0));
	// make the z from pythagorean formula - our angle is measured from the horizontal plane
	GLOBAL.CAMERA_LOOK_VECTOR.z = 5 * tan(angleV*PI/180.0);

	if(dx==0 && dy==0)
		return; //we are not really doing anything, so we will simply ignore this thing


	glutWarpPointer(midX,GLOBAL.WINDOW_MAX_Y-midY);
}

void thirdPerson_CameraMovement(int x, int y, Point center){//Camera orbits the tank, focused on the tank (over the shoulder view)
	double movementDivisor = 6.0;
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
	if(angleV<-20)angleV=-20;




	GLOBAL.CAMERA_POS.x = center.x + 4.0*cos(angleH*PI/180.0);//camera rotates around the center at a radius of 4
	GLOBAL.CAMERA_POS.y = center.y + 4.0*-sin(angleH*PI/180.0);
	GLOBAL.CAMERA_POS.z = ( center.z + sin(angleV*PI/180.0 ) ) +3.0;
	// GLOBAL.CAMERA_POS.z=2;



	// GLOBAL.CAMERA_LOOK_VECTOR.x = center.x - GLOBAL.CAMERA_POS.x;//look at the center
	// GLOBAL.CAMERA_LOOK_VECTOR.y = center.y - GLOBAL.CAMERA_POS.y;
	// GLOBAL.CAMERA_LOOK_VECTOR.z = center.z - GLOBAL.CAMERA_POS.z +2;
	// double zz = asin()
	GLOBAL.CAMERA_LOOK_VECTOR.x = (center.x+100000)*-cos(angleH*PI/180.0);//circle with radius 1000 - far off focal point
	GLOBAL.CAMERA_LOOK_VECTOR.y = (center.y+100000)*sin(angleH*PI/180.0);
	GLOBAL.CAMERA_LOOK_VECTOR.z = (center.z+100000)*sin(angleV*PI/180.0);

	


	// 
	if(dx==0 && dy==0)
		return; //we are not really doing anything, so we will simply ignore this thing

	glutWarpPointer(midX,GLOBAL.WINDOW_MAX_Y-midY);

}

void drawAxies(){
	static unsigned int listName = 0;
	if(listName!=0){
		glCallList(listName);
	}else{
		listName = glGenLists(1);
		glNewList(listName,GL_COMPILE);

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

		glEndList();
	}

}

void updateLights(){
	glLightfv(GL_LIGHT0,GL_AMBIENT,GLOBAL.LIGHTS[0].color_ambient);
}