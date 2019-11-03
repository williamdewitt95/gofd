#include "groundbox.h"

Groundbox::Groundbox(double buildingWidth, double streetWidth, double sidewalkWidth)
{
	//We want the groundbox to completely fill the arena. I had originally planned to put down a black base, before
	//adding in road that were texture mapped along the newer strips that were placed above the base, but ran out of time.
	//Base takes values from building to ensure that the entire arena has ground.
	double base = buildingWidth*(NUM_BLOCKS_WIDE) + streetWidth*(NUM_BLOCKS_WIDE-1) -buildingWidth/2 + sidewalkWidth;
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		//Turns out there was a little more than just base, so I added those in with building and street widths. Probably could
		// have factored it in.
		points.push_back(Point( -buildingWidth/2 - sidewalkWidth, -buildingWidth/2 - sidewalkWidth, 0));
		points.push_back(Point( base, -buildingWidth/2 - sidewalkWidth, 0));
		points.push_back(Point( base,  base, 0));
		points.push_back(Point( -buildingWidth/2 -sidewalkWidth,  base, 0));
		points.push_back(Point( -buildingWidth/2 - sidewalkWidth, -buildingWidth/2 - sidewalkWidth, 0));


	}
	//The walls were to prevent people from looking off the edge into oblivion. They were originally just dark colored,
	//but eventually were mapped to brick textures.
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
	//That was supposed to be dark grey. Turned out pretty asphalty, so I liked it.
	for(int i = 0; i < this->model.size(); i++)
		this->model[i].draw();
	glPopMatrix();
}
