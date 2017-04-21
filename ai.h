#ifndef AI
#define AI

#include "globals.h"
#include "building.h"
#include "target.h"
#include "mapnode.h"
#include <queue>
#include <ctime>

class AI_Tank{



public:
	AI_Tank(Tank *tank, Tank *enemy);
	Tank *tank;
	int grid[15][15];

	int mapGrid[100][100];
	int checkedMap[100][100];
	int uncheckedMap[100][100];
	int directionalMap[100][100];
	
	int n, m, dir, maxTankDist;

	int dx[8]; 
	int dy[8];


	Point start;
	Point destination;
	void forwards();//go forwards
	void forwards(double speed);
	bool turn(double direction);//target angle
	void stop();//stop or do nothing


	void calculatePath();//int x, int y);//create a new path to new grid coordinate

	std::string findPath(const int & xStart, const int &yStart, const int &xEnd, const int &yEnd);

	void update_AI();//give current command on what to do
	void updateTank(Tank* enemy);

	void findNearestBuilding(Point center);
	void nearbyTarget(Tank * enemy);//check where the enemy is in comparison to where we are
	void aim(Point enemy);//aim the turret at the enemy

	void fillMap();
	void followRoute();	

	void setRoute();
	std::string route;


	// for a star
	bool initialized;
	double startX;
	double startY;
	double destX;
	double destY;

};




#endif


