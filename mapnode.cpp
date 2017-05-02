#include "mapnode.h"

	// Herron: class of nodes to be used in astar search algorithm

	MapNode::MapNode(int xPos, int yPos, int d, int p){
		xpos = xPos;
                ypos = yPos;
                level = d;
                priority = p;
	}

	// Herron: accessors
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

	// Herron: increases priority of node
       	void MapNode::priorityUpdate(const int &xDest, const int &yDest){
		priority = level+estimateDistance(xDest, yDest)*10;
	}

	// Herron: increments level of node
       	void MapNode::incLevel( const int &i){
		level+= (dir==4?(i%2==0?10:14):10);//(dir%2);
	}

	// Herron: returns distance between current node and destination
        const int& MapNode::estimateDistance(const int &xDest, const int &yDest){
		static int xd, yd, d;

		xd = xDest-xpos;
		yd = yDest-ypos;

		d = (int) sqrt(xd*xd+yd*yd);

		return d;
	}

	// Herron: returns node of highest priority
	bool operator<(const MapNode& a, const MapNode& b){
        return a.getPriority() > b.getPriority();
	}
