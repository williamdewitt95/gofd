#include "groundbox.h"

Groundbox::Groundbox(double buildingWidth, double streetWidth, double sidewalkWidth)
{
	double base = buildingWidth*(NUM_BLOCKS_WIDE) + streetWidth*(NUM_BLOCKS_WIDE-1) -buildingWidth/2 + sidewalkWidth;
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();

		points.push_back(Point( -buildingWidth/2 - sidewalkWidth, -buildingWidth/2 - sidewalkWidth, 0));
		points.push_back(Point( base, -buildingWidth/2 - sidewalkWidth, 0));
		points.push_back(Point( base,  base, 0));
		points.push_back(Point( -buildingWidth/2 -sidewalkWidth,  base, 0));
		points.push_back(Point( -buildingWidth/2 - sidewalkWidth, -buildingWidth/2 - sidewalkWidth, 0));


	}
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		loadTex("textures/buildings/brick1.png");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/buildings/brick1.png"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point( -buildingWidth/2 - sidewalkWidth, -buildingWidth/2 - sidewalkWidth, 0));
		points.push_back(Point( -buildingWidth/2 - sidewalkWidth, base, 0));
		points.push_back(Point( -buildingWidth/2 - sidewalkWidth,  base, 10));
		points.push_back(Point( -buildingWidth/2 - sidewalkWidth,  -buildingWidth/2 - sidewalkWidth, 10));
		points.push_back(Point( -buildingWidth/2 - sidewalkWidth, -buildingWidth/2 - sidewalkWidth, 0));

		texs.push_back(Point( 0,0,0));
		texs.push_back(Point( 0, 2,0));
		texs.push_back(Point((base + buildingWidth/2 + sidewalkWidth)/5, 2, 0));
		texs.push_back(Point((base + buildingWidth/2 + sidewalkWidth)/5, 0, 0));
		texs.push_back(Point(0, 0, 0));
	}
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/buildings/brick1.png"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point( -buildingWidth/2 - sidewalkWidth, -buildingWidth/2 - sidewalkWidth, 0));
		points.push_back(Point( -buildingWidth/2 - sidewalkWidth, -buildingWidth/2 - sidewalkWidth, 10));
		points.push_back(Point( base,  -buildingWidth/2 - sidewalkWidth, 10));
		points.push_back(Point( base,  -buildingWidth/2 - sidewalkWidth, 0));
		points.push_back(Point( -buildingWidth/2 - sidewalkWidth, -buildingWidth/2 - sidewalkWidth, 0));

		texs.push_back(Point( 0,0,0));
		texs.push_back(Point( 0, 2,0));
		texs.push_back(Point((base + buildingWidth/2 + sidewalkWidth)/5, 2, 0));
		texs.push_back(Point((base + buildingWidth/2 + sidewalkWidth)/5, 0, 0));
		texs.push_back(Point(0, 0, 0));
	}
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/buildings/brick1.png"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point( base, -buildingWidth/2 - sidewalkWidth, 0));
		points.push_back(Point( base, -buildingWidth/2 - sidewalkWidth, 10));
		points.push_back(Point( base, base, 10));
		points.push_back(Point( base, base, 0));
		points.push_back(Point( base, -buildingWidth/2 - sidewalkWidth, 0));

		texs.push_back(Point( 0,0,0));
		texs.push_back(Point( 0, 2,0));
		texs.push_back(Point((base + buildingWidth/2 + sidewalkWidth)/5, 2, 0));
		texs.push_back(Point((base + buildingWidth/2 + sidewalkWidth)/5, 0, 0));
		texs.push_back(Point(0, 0, 0));
	}
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/buildings/brick1.png"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point( -buildingWidth/2 - sidewalkWidth, base, 0));
		points.push_back(Point( base, base, 0));
		points.push_back(Point( base, base, 10));
		points.push_back(Point( -buildingWidth/2 - sidewalkWidth, base, 10));
		points.push_back(Point( -buildingWidth/2 - sidewalkWidth, base, 0));

		texs.push_back(Point( 0,0,0));
		texs.push_back(Point( 0, 2,0));
		texs.push_back(Point((base + buildingWidth/2 + sidewalkWidth)/5, 2, 0));
		texs.push_back(Point((base + buildingWidth/2 + sidewalkWidth)/5, 0, 0));
		texs.push_back(Point(0, 0, 0));
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
