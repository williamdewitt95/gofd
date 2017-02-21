#include "mapnode.h"

	MapNode::MapNode(int xPos, int yPos, int d, int p){
		xpos = xPos;
                ypos = yPos;
                level = d;
                priority = p;
	}

        int MapNode::getXPos(){
		return this.xpos;
	}

        int MapNode::getYPos(){
		return this.ypos;
	}

        int MapNode::getLevel(){
		return this.level;		
	}

        int MapNode::getPriority(){
		return this.priority;
	}

       	void MapNode::priorityUpdate(int &xDest, int &yDest){
		priority = level+estimateDistance(xDest, yDest)*10;
	}

       	void MapNode::incLevel(int &dir){
		level+=(i%2);
	}

        int MapNode::&estimateDistance(int &xDest, int &yDest){
		static int xd, yd, d;

		xd = xDest-xpos;
		yd = yDest-ypos;

		d = (int) sqrt(xd*xd+yd*yd);

		return d;
	}
