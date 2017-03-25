#include "mapnode.h"

	MapNode::MapNode(int xPos, int yPos, int d, int p){
		xpos = xPos;
                ypos = yPos;
                level = d;
                priority = p;
	}

        int MapNode::getXPos() const{
		return xpos;
	}

        int MapNode::getYPos() const{
		return ypos;
	}

        int MapNode::getLevel() const{
		return level;		
	}

        int MapNode::getPriority() const{
		return priority;
	}

       	void MapNode::priorityUpdate(const int &xDest, const int &yDest){
		priority = level+estimateDistance(xDest, yDest)*10;
	}

       	void MapNode::incLevel( const int &i){
		level+=(dir%2);
	}

        const int& MapNode::estimateDistance(const int &xDest, const int &yDest){
		static int xd, yd, d;

		xd = xDest-xpos;
		yd = yDest-ypos;

		d = (int) sqrt(xd*xd+yd*yd);

		return d;
	}

	/*bool operator<( const MapNode &other) const{
		this.getPriority() > other.getPriority();
	}*/

	bool operator<(const MapNode& a, const MapNode& b){
        return a.getPriority() > b.getPriority();
	}
