#ifndef AI
#define AI

#include "globals.h"
#include "building.h"



class AI_Tank{



public:
	AI_Tank(Tank *tank);
	Tank *tank;
	int grid[15][15];
	
	// set map dimensions
	//static int m = 100, n = 100;
	
	int mapGrid[100][100];
	int checkedMap[100][100];
	int uncheckedMap[100][100];
	int directionalMap[100][100];
	
	//static const int numDir = 8;
	
	enum {numDir = 8};

	//const int dx[numDir]; //= {1, 1, 0, -1, -1, 0, 1};
	//const int dy[numDir]; // = {0, 1, 1, 1, 0, -1, -1, -1};

	Point destination;
	void forwards();//go forwards
	void forwards(double speed);
	bool turn(double direction);//target angle
	void stop();//stop or do nothing


	void calculatePath(int x, int y);//create a new path to new grid coordinate


	void update_AI();//give current command on what to do
	void updateTank();

	void findNearestBuilding(Point center);
	void nearbyTarget(Tank * enemy);//check where the enemy is in comparison to where we are
	void aim(Point enemy);//aim the turret at the enemy
};




#endif


