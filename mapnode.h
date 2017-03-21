#ifndef MAP_NODE
#define MAP_NODE

#include <math.h> 

class MapNode{

	int xpos, ypos, level, priority;

	public:
		MapNode(int xPos, int yPos, int d, int p);

		int dir;

		int getXPos() const;
		int getYPos() const;
		int getLevel() const;
		int getPriority() const;
		
		void priorityUpdate(const int &xDest, const int &yDest);
		
		void incLevel(const int &dir);

		const int& estimateDistance(const int &xDest, const int &yDest);

		//bool operator<(const MapNode &other) const;
				
};

bool operator<(const MapNode& a, const MapNode& b);

#endif
