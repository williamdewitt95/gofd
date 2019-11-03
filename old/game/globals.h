#ifndef GLOP_GLOBALS
#define GLOP_GLOBALS

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <limits>
#include <ctime>
#include "polygon3d.h"
#include "SOIL.h"
#include "drawableObject.h"
#include "vector_basics.h"


#define PI 3.14159265358979
#define NUM_BLOCKS_WIDE 15
#define GRAVITY 9.81
#define TIME_LIMIT 602 //extra 2 seconds since there's ~2sec gap from creation of global obj and opening of window
#define NUM_AI_TANKS 20

struct LIGHT_STRUCT{
	GLfloat attenuation_linear;
	GLfloat attenuation_quadratic;
	GLfloat position[4]; //XYZ 1 - this last index should always be one
	GLfloat color_ambient[4];
	GLfloat color_diffuse[4];
	GLfloat color_specular[4];
	GLfloat spotlight_direction[3];
};

struct MODEL_TRIANGLES{
	//use this to represent basic triangels from your model
	bool hasTexture;
	GLuint texture;
	double texturePoints[3]; // at each vertex, what part of the texture is dispalyed
	double p1[3];
	double p2[3];
	double p3[3];
};

struct TextureInfo{
	std::string name;
	int width,height;
	GLuint textureRef;
};
void loadTex(std::string name);

class GLOBAL_SETTINGS{
public:
	GLOBAL_SETTINGS();
	GLFWwindow* windowHandle;
	int WINDOW_MAX_X;
	int WINDOW_MAX_Y;

	int score;
	time_t timeStart;
	bool gameOver;
	bool gameExitRequest;

	struct {
		double x;
		double y;
		double z;
	} CAMERA_POS;
	struct {
		double x;
		double y;
		double z;
	} CAMERA_LOOK_VECTOR;
	double CAMERA_ANGLE_VERTICAL;
	double CAMERA_ANGLE_HORIZONTAL;
	struct {
		double x;
		double y;
	} prevMouseVirtCoords;
	
	void reset();

	LIGHT_STRUCT LIGHTS[8];
	std::unordered_map<std::string,TextureInfo> TEXTURES_LOADED; // allows for easily shared textures, if they use the same name, they get the same texture
};

extern GLOBAL_SETTINGS GLOBAL;
//extern Tank * tank;


class Building;
extern std::vector<Building*> buildings;

class Projectile;
extern std::vector<Projectile*> projectiles;

class Tank;
extern Tank * tank;

class AI_Tank;
extern std::vector<AI_Tank *> ai_tanks;

class Target;
extern std::vector<Target*> targets;


void windowResize(GLFWwindow* window,int width, int height);
void cameraMovement(double dx, double dy, int cameraMode);
void FPS_CameraMovement(double dx, double dy, Point center);
void thirdPerson_CameraMovement(double dx, double dy, Point center);
void free_CameraMovement(double dx, double dy);
void drawTank (void);
void drawAxies();
void updateLights();

#include "projectile.h"
#include "building.h"
#include "tank.h"
#include "ai.h"
#include "target.h"
#include "hud.h"
#include "skybox.h"
#include "groundbox.h"
#include "collisions.h"

#endif
