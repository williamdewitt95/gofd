#include "groundbox.h"

Groundbox::Groundbox(double buildingWidth, double streetWidth)
{
	double base = buildingWidth*NUM_BLOCKS_WIDE + streetWidth*NUM_BLOCKS_WIDE;
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();

		points.push_back(Point( 0, 0, 0));
		points.push_back(Point( base, 0, 0));
		points.push_back(Point( base,  base, 0));
		points.push_back(Point( 0,  base, 0));
		points.push_back(Point( 0, 0, 0));
	}
}

void Groundbox::draw()
{
	glPushMatrix();
	glColor3i(105, 105, 105);
	for(int i = 0; i < this->model.size(); i++)
		this->model[i].draw();
	glPopMatrix();
}
