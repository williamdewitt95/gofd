#include "globals.h"
#include "building.h"

GLOBAL_SETTINGS::GLOBAL_SETTINGS(){
	windowHandle = NULL;

	WINDOW_MAX_X = 1000;
	WINDOW_MAX_Y = 1000;

	score = 0;
	timeStart = time(0);
	gameOver = false;
	gameExitRequest = false;

	CAMERA_POS = {Building::distanceBetweenBuildings/2.0,
	              Building::distanceBetweenBuildings/2.0,
	              2
			};
	CAMERA_LOOK_VECTOR = {0,1,0};
	CAMERA_ANGLE_VERTICAL = 0;
	CAMERA_ANGLE_HORIZONTAL = 90;
	prevMouseVirtCoords = {0,0};

	LIGHTS[0].position[0]=0;
	LIGHTS[0].position[1]=0;
	LIGHTS[0].position[2]=0;
	LIGHTS[0].position[3]=1;
	LIGHTS[0].attenuation_linear=0.0001;
	LIGHTS[0].attenuation_quadratic=0.001;
	LIGHTS[0].color_ambient[0]=0.0;
	LIGHTS[0].color_ambient[1]=0.0;
	LIGHTS[0].color_ambient[2]=0.0;
	LIGHTS[0].color_ambient[3]=1.0;
	LIGHTS[0].color_diffuse[0]=1.0;
	LIGHTS[0].color_diffuse[1]=1.0;
	LIGHTS[0].color_diffuse[2]=1.0;
	LIGHTS[0].color_diffuse[3]=1.0;
	LIGHTS[0].color_specular[0]=0.01;
	LIGHTS[0].color_specular[1]=0.01;
	LIGHTS[0].color_specular[2]=0.01;
	LIGHTS[0].color_specular[3]=1.0;
	LIGHTS[0].spotlight_direction[0] = -1.0;
	LIGHTS[0].spotlight_direction[1] = -0.01;
	LIGHTS[0].spotlight_direction[2] = -0.1;


	LIGHTS[1].position[0] = 0.0;
	LIGHTS[1].position[1] = 0.0;
	LIGHTS[1].position[2] = 1000.0;
	LIGHTS[1].position[3] = 0.0;
    LIGHTS[1].color_ambient[0] = 0.35;
    LIGHTS[1].color_ambient[1] = 0.35;
    LIGHTS[1].color_ambient[2] = 0.35;
    LIGHTS[1].color_ambient[3] = 1.0;
    LIGHTS[1].color_diffuse[0] = 0.0;
    LIGHTS[1].color_diffuse[1] = 0.0;
    LIGHTS[1].color_diffuse[2] = 0.0;
    LIGHTS[1].color_diffuse[3] = 1.0;
    LIGHTS[1].color_specular[0] = 0.0;
    LIGHTS[1].color_specular[1] = 0.0;
    LIGHTS[1].color_specular[2] = 0.0;
    LIGHTS[1].color_specular[3] = 1.0;
    LIGHTS[1].attenuation_linear=0.0001;
	LIGHTS[1].attenuation_quadratic=0.001;
	LIGHTS[1].spotlight_direction[0] = 0.0;
	LIGHTS[1].spotlight_direction[1] = 0.0;
	LIGHTS[1].spotlight_direction[2] = 1.0;


	LIGHTS[2].position[0] = 0.0;
	LIGHTS[2].position[1] = 0.0;
	LIGHTS[2].position[2] = 100.0;
	LIGHTS[2].position[3] = 1.0;
    LIGHTS[2].color_ambient[0] = 0.0;
    LIGHTS[2].color_ambient[1] = 0.0;
    LIGHTS[2].color_ambient[2] = 0.0;
    LIGHTS[2].color_ambient[3] = 1.0;
    LIGHTS[2].color_diffuse[0] = 0.5;
    LIGHTS[2].color_diffuse[1] = 0.5;
    LIGHTS[2].color_diffuse[2] = 0.5;
    LIGHTS[2].color_diffuse[3] = 1.0;
    LIGHTS[2].color_specular[0] = 0.1;
    LIGHTS[2].color_specular[1] = 0.1;
    LIGHTS[2].color_specular[2] = 0.1;
    LIGHTS[2].color_specular[3] = 1.0;
    LIGHTS[2].attenuation_linear=0.01;
	LIGHTS[2].attenuation_quadratic=0.01;
	LIGHTS[2].spotlight_direction[0] = 0.01;
	LIGHTS[2].spotlight_direction[1] = 0.01;
	LIGHTS[2].spotlight_direction[2] =-1.0;
}

GLOBAL_SETTINGS GLOBAL;

void GLOBAL_SETTINGS::reset()
{
	score = 0;
	timeStart = time(0);
	gameOver = false;

	CAMERA_POS = {Building::distanceBetweenBuildings/2.0,
	              Building::distanceBetweenBuildings/2.0,
	              2
			};
	CAMERA_LOOK_VECTOR = {0,1,0};
	CAMERA_ANGLE_VERTICAL = 0;
	CAMERA_ANGLE_HORIZONTAL = 90;

	LIGHTS[0].position[0]=0;
	LIGHTS[0].position[1]=0;
	LIGHTS[0].position[2]=0;
	LIGHTS[0].position[3]=1;
	LIGHTS[0].attenuation_linear=0.0001;
	LIGHTS[0].attenuation_quadratic=0.001;
	LIGHTS[0].color_ambient[0]=0.0;
	LIGHTS[0].color_ambient[1]=0.0;
	LIGHTS[0].color_ambient[2]=0.0;
	LIGHTS[0].color_ambient[3]=1.0;
	LIGHTS[0].color_diffuse[0]=1.0;
	LIGHTS[0].color_diffuse[1]=1.0;
	LIGHTS[0].color_diffuse[2]=1.0;
	LIGHTS[0].color_diffuse[3]=1.0;
	LIGHTS[0].color_specular[0]=0.01;
	LIGHTS[0].color_specular[1]=0.01;
	LIGHTS[0].color_specular[2]=0.01;
	LIGHTS[0].color_specular[3]=1.0;

	LIGHTS[1].position[0] = 0.0;
	LIGHTS[1].position[1] = 0.0;
	LIGHTS[1].position[2] = 1000.0;
	LIGHTS[1].position[3] = 0.0;
    LIGHTS[1].color_ambient[0] = 0.0;
    LIGHTS[1].color_ambient[1] = 0.0;
    LIGHTS[1].color_ambient[2] = 0.0;
    LIGHTS[1].color_ambient[3] = 1.0;
    LIGHTS[1].color_diffuse[0] = 0.9;
    LIGHTS[1].color_diffuse[1] = 0.9;
    LIGHTS[1].color_diffuse[2] = 0.9;
    LIGHTS[1].color_diffuse[3] = 1.0;
    LIGHTS[1].color_specular[0] = 0.1;
    LIGHTS[1].color_specular[1] = 0.1;
    LIGHTS[1].color_specular[2] = 0.1;
    LIGHTS[1].color_specular[3] = 1.0;
    LIGHTS[1].attenuation_linear=0.0001;
	LIGHTS[1].attenuation_quadratic=0.001;
	LIGHTS[1].spotlight_direction[0] = 0.0;
	LIGHTS[1].spotlight_direction[1] = 0.0;
	LIGHTS[1].spotlight_direction[2] = 1.0;


	LIGHTS[2].position[0] = 0.0;
	LIGHTS[2].position[1] = 0.0;
	LIGHTS[2].position[2] = 100.0;
	LIGHTS[2].position[3] = 1.0;
    LIGHTS[2].color_ambient[0] = 0.0;
    LIGHTS[2].color_ambient[1] = 0.0;
    LIGHTS[2].color_ambient[2] = 0.0;
    LIGHTS[2].color_ambient[3] = 1.0;
    LIGHTS[2].color_diffuse[0] = 0.5;
    LIGHTS[2].color_diffuse[1] = 0.5;
    LIGHTS[2].color_diffuse[2] = 0.5;
    LIGHTS[2].color_diffuse[3] = 1.0;
    LIGHTS[2].color_specular[0] = 0.1;
    LIGHTS[2].color_specular[1] = 0.1;
    LIGHTS[2].color_specular[2] = 0.1;
    LIGHTS[2].color_specular[3] = 1.0;
    LIGHTS[2].attenuation_linear=0.01;
	LIGHTS[2].attenuation_quadratic=0.01;
	LIGHTS[2].spotlight_direction[0] = 0.01;
	LIGHTS[2].spotlight_direction[1] = 0.01;
	LIGHTS[2].spotlight_direction[2] =-1.0;
}

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

void windowResize(GLFWwindow* window,int width, int height){

	//remember what the new size of the window is
	GLOBAL.WINDOW_MAX_X = width;
	GLOBAL.WINDOW_MAX_Y = height;

	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();
	// gluOrtho2D(WORLD_COORDINATE_MIN_X, WORLD_COORDINATE_MAX_X,  // do the scale again
	//           WORLD_COORDINATE_MIN_Y, WORLD_COORDINATE_MAX_Y);

	//make the scene visable over the whole window
	glViewport(0,0,width,height);
	//glutPostRedisplay();
}

void cameraMovement(double dx, double dy, int cameraMode){
	switch(cameraMode){
		case 0:
			free_CameraMovement(dx,dy);
			break;
		case 1:
			FPS_CameraMovement(dx,dy,tank->center);

			break;
		case 2:
			thirdPerson_CameraMovement(dx,dy,tank->center);
			break;
	}
	
}
void FPS_CameraMovement(double dx, double dy, Point center){//first person is actually sitting on top of turret
	double movementDivisor = 3.0;

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
	// GLOBAL.CAMERA_POS.z = center_z + sin(angleV*PI/180.0)+2;
	GLOBAL.CAMERA_POS.z=2;

	// printf("PassiveFunc\t%dx%d\n",dx,dy); // pixel deltas
	// printf("angles\t%f %f\n",angleH,angleV); // look angles
	// printf("CAMERA_LOOK_VECTOR\t%.2f %.2f %.2f\n",GLOBAL.CAMERA_LOOK_VECTOR.x,GLOBAL.CAMERA_LOOK_VECTOR.y,GLOBAL.CAMERA_LOOK_VECTOR.z); // look vector
	// printf("CAMERA_POS\t%.2f %.2f %.2f\n",GLOBAL.CAMERA_POS.x,GLOBAL.CAMERA_POS.y,GLOBAL.CAMERA_POS.z); // position 
}

void free_CameraMovement(double dx, double dy){//move the camera around not bound to the tank
	double movementDivisor = 6.0;
	
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
}

void thirdPerson_CameraMovement(double dx, double dy, Point center){//Camera orbits the tank, focused on the tank (over the shoulder view)
	double movementDivisor = 6.0;

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

	// GLOBAL.CAMERA_LOOK_VECTOR.x = center.x - GLOBAL.CAMERA_POS.x;//look at the center
	// GLOBAL.CAMERA_LOOK_VECTOR.y = center.y - GLOBAL.CAMERA_POS.y;
	// GLOBAL.CAMERA_LOOK_VECTOR.z = center.z - GLOBAL.CAMERA_POS.z +2;
	// double zz = asin()
	GLOBAL.CAMERA_LOOK_VECTOR.x = (center.x+100000)*-cos(angleH*PI/180.0);//circle with radius 1000 - far off focal point
	GLOBAL.CAMERA_LOOK_VECTOR.y = (center.y+100000)*sin(angleH*PI/180.0);
	GLOBAL.CAMERA_LOOK_VECTOR.z = (center.z+100000)*sin(angleV*PI/180.0);
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
			glTranslated(10,0,0);
			glScaled(4.0/104.76,4.0/104.76,4.0/104.76);
			//glutStrokeCharacter(GLUT_STROKE_ROMAN,'X');
		glPopMatrix();
		glPushMatrix();
			glTranslated(0,10,0);
			glScaled(4.0/104.76,4.0/104.76,4.0/104.76);
			//glutStrokeCharacter(GLUT_STROKE_ROMAN,'Y');
		glPopMatrix();
		glPushMatrix();
			glTranslated(0,0,10);
			glScaled(4.0/104.76,4.0/104.76,4.0/104.76);
			glRotated(90,1,0,0);
			//glutStrokeCharacter(GLUT_STROKE_ROMAN,'Z');
		glPopMatrix();

		glEndList();
	}

}

void updateLights(){
	GLfloat temp[]={1.0,1.0,1.0,1.0};
	glMaterialfv(GL_FRONT,GL_SPECULAR,temp);

	glLightfv(GL_LIGHT0,GL_POSITION,GLOBAL.LIGHTS[0].position      );
	glLightfv(GL_LIGHT0,GL_AMBIENT ,GLOBAL.LIGHTS[0].color_ambient );
	glLightfv(GL_LIGHT0,GL_DIFFUSE ,GLOBAL.LIGHTS[0].color_diffuse );
	glLightfv(GL_LIGHT0,GL_SPECULAR,GLOBAL.LIGHTS[0].color_specular);
	glLightf (GL_LIGHT0,GL_LINEAR_ATTENUATION,GLOBAL.LIGHTS[0].attenuation_linear);
	glLightf (GL_LIGHT0,GL_QUADRATIC_ATTENUATION,GLOBAL.LIGHTS[0].attenuation_quadratic);
	

	glLightfv(GL_LIGHT1,GL_POSITION,GLOBAL.LIGHTS[1].position      );
	glLightfv(GL_LIGHT1,GL_AMBIENT ,GLOBAL.LIGHTS[1].color_ambient );
	glLightfv(GL_LIGHT1,GL_DIFFUSE ,GLOBAL.LIGHTS[1].color_diffuse );
	glLightfv(GL_LIGHT1,GL_SPECULAR,GLOBAL.LIGHTS[1].color_specular);
	glLightf (GL_LIGHT1,GL_LINEAR_ATTENUATION,GLOBAL.LIGHTS[1].attenuation_linear);
	glLightf (GL_LIGHT1,GL_QUADRATIC_ATTENUATION,GLOBAL.LIGHTS[1].attenuation_quadratic);

	
	GLfloat light_2_spot_cutoff = 45.0;
	GLfloat light_2_spot_exponent = 0;//64

	glLightfv(GL_LIGHT2,GL_POSITION,GLOBAL.LIGHTS[2].position      );
	glLightfv(GL_LIGHT2,GL_AMBIENT ,GLOBAL.LIGHTS[2].color_ambient );
	glLightfv(GL_LIGHT2,GL_DIFFUSE ,GLOBAL.LIGHTS[2].color_diffuse );
	glLightfv(GL_LIGHT2,GL_SPECULAR,GLOBAL.LIGHTS[2].color_specular);
	// glLightf (GL_LIGHT2,GL_LINEAR_ATTENUATION,GLOBAL.LIGHTS[2].attenuation_linear);
	// glLightf (GL_LIGHT2,GL_QUADRATIC_ATTENUATION,GLOBAL.LIGHTS[2].attenuation_quadratic);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, GLOBAL.LIGHTS[2].spotlight_direction);
	glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, &light_2_spot_cutoff);
	glLightfv(GL_LIGHT2, GL_SPOT_EXPONENT, &light_2_spot_exponent);


}
