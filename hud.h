

#include "globals.h"
#include "tank.h"
#ifndef gameHUD
#define gameHUD

	// int oldTime, currentTime;
	// float actualfps, fps;

	void drawHealthBar(Tank tank);
	void drawCooldownBar(Tank tank);
	void drawScore();
	void showFPS(float &fps, int &oldTime, float &actualfps);




#endif
