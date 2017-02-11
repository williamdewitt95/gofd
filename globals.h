#ifndef GLOP_GLOBALS
#define GLOP_GLOBALS

#include <GL/glut.h>
#include <GL/glu.h>
#include <vector>
#include <unordered_map>
#include <string>
#include "imageLibrary/image.h"
#include "tank.h"
#include "polygon3d.h"

#define PI 3.14159265358979

struct LIGHT_STRUCT{
	double attenuation_linear;
	double attenuation_quadratic;
	double possition[3];
	double color[3];
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
	unsigned long width,height;
	GLuint textureRef;
};
void loadTex(std::string name);

class GLOBAL_SETTINGS{
public:
	GLOBAL_SETTINGS();
	int WINDOW_MAX_X;
	int WINDOW_MAX_Y;

	double WORLD_COORDINATE_MIN_X;
	double WORLD_COORDINATE_MAX_X;
	double WORLD_COORDINATE_MIN_Y;
	double WORLD_COORDINATE_MAX_Y;

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

	std::vector<LIGHT_STRUCT> LIGHTS;
	std::unordered_map<std::string,TextureInfo> TEXTURES_LOADED; // allows for easily shared textures, if they use the same name, they get the same texture
};

extern GLOBAL_SETTINGS GLOBAL;
//extern Tank * tank;

void windowResize(int width, int height);
void scaleMouse(int &x, int &y);
void FPS_CameraMovement(int x, int y, Point center);
void FPS_CameraMovement(int x, int y);
void drawTank (void);

#endif
