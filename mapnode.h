#ifndef MAP_NODE
#define MAP_NODE

class MapNode{

	int xpos, ypos, level, priority;

	public:
		MapNode(int xPos, int yPos, int d, int p);

		int getXPos();
		int getYPos();
		int getLevel();
		int getPriority();
		
		void priorityUpdate(int &xDest, int &yDest);
		
		void incLevel(int &dir);

		int& estimateDistance(int &xDest, int &yDest);

		bool operator<(const node &other);
				
}
#endif
