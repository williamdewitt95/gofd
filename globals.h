#ifndef GLOP_GLOBALS
#define GLOP_GLOBALS

#include <GL/glew.h> 

#include <GL/glut.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <string.h>
// #include "imageLibrary/image.h"
#include "polygon3d.h"
#include "SOIL.h"
#include "drawableObject.h"


#define PI 3.14159265358979
#define NUM_BLOCKS_WIDE 15
#define GRAVITY 9.81
#define NUM_LIGHTS 10

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


	// LIGHT_STRUCT LIGHTS[8];
	std::unordered_map<std::string,TextureInfo> TEXTURES_LOADED; // allows for easily shared textures, if they use the same name, they get the same texture


	float g_lightPosition[NUM_LIGHTS * 3];
	float g_lightColor[NUM_LIGHTS * 3];
	float g_lightRotation;
	GLuint shaderProgram;
	GLuint shader_ProgramCameraPositionLocation;
	GLuint shader_ProgramLightPositionLocation;
	GLuint shader_ProgramLightColorLocation;
	GLuint shader_ProgramNumberOfLights;
	GLint baseImageLoc;

};

extern GLOBAL_SETTINGS GLOBAL;
//extern Tank * tank;


class Building;
extern std::vector<Building*> buildings;

class Projectile;
extern std::vector<Projectile*> projectiles;

static GLuint g_cylinderBufferId;
static unsigned int g_cylinderNumVertices;

static float g_cameraPosition[3];




void windowResize(int width, int height);
void scaleMouse(int &x, int &y);
void cameraMovement(int x, int y, Point center, int cameraMode);
void FPS_CameraMovement(int x, int y, Point center);
void thirdPerson_CameraMovement(int x, int y, Point center);
void free_CameraMovement(int x, int y);
void drawTank (void);
void drawAxies();
void updateLights();
void loadShader();

#endif
