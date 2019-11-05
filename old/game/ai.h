#ifndef AI
#define AI

#include "globals.h"
#include "building.h"
#include "tank.h"


class AI_Tank{



public:
	float lookupTable[169];
	AI_Tank(Tank *tank);
	Tank *tank;
	int grid[15][15];
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

	float lookup(int distance);
	void initializeLookupTable();
};




#endif


