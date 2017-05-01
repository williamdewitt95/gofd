#include "skybox.h"

Skybox::Skybox()
{
	unsigned char color[3]={128,128,128};
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		loadTex("textures/Skybox/skyboxcubemap.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/Skybox/skyboxcubemap.jpg"].textureRef);
		model[model.size()-1].setColor(color[0],color[1],color[2]);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point( 999, -1000, -1000));
		points.push_back(Point( 999, -1000,  1000));
		points.push_back(Point( 999,  1000,  1000));
		points.push_back(Point( 999,  1000, -1000));
		points.push_back(Point( 999, -1000, -1000));
		texs.push_back(Point(.33,  0,  0));
		texs.push_back(Point(.66,  0,  0));
		texs.push_back(Point(.66, .25, 0));
		texs.push_back(Point(.33, .25, 0));
		texs.push_back(Point(.33, 0, 0));
	}
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		loadTex("textures/Skybox/skyboxcubemapreversed.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/Skybox/skyboxcubemap.jpg"].textureRef);
		model[model.size()-1].setColor(color[0],color[1],color[2]);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point( -999, -1000, -1000));
		points.push_back(Point( -999,  1000, -1000));
		points.push_back(Point( -999,  1000,  1000));
		points.push_back(Point( -999, -1000,  1000));
		points.push_back(Point( -999, -1000, -1000));
		texs.push_back(Point(.33, .75, 0));
		texs.push_back(Point(.33, .50, 0));
		texs.push_back(Point(.66, .50, 1));
		texs.push_back(Point(.66, .75, 1));
		texs.push_back(Point(.33, .75, 0));
	}
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		//loadTex("textures/Skybox/skyboxcubemap.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/Skybox/skyboxcubemap.jpg"].textureRef);
		model[model.size()-1].setColor(color[0],color[1],color[2]);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point( -1000,  999, -1000));
		points.push_back(Point(  1000,  999, -1000));
		points.push_back(Point(  1000,  999,  1000));
		points.push_back(Point( -1000,  999,  1000));
		points.push_back(Point( -1000,  999, -1000));
		texs.push_back(Point(.33, .50, 0));
		texs.push_back(Point(.33, .25, 0));
		texs.push_back(Point(.66, .25, 0));
		texs.push_back(Point(.66, .50, 0));
		texs.push_back(Point(.33, .50, 0));
	}
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		//loadTex("textures/Skybox/skyboxcubemap.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/Skybox/skyboxcubemap.jpg"].textureRef);
		model[model.size()-1].setColor(color[0],color[1],color[2]);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point( -1000, -999, -1000));
		points.push_back(Point( -1000, -999,  1000));
		points.push_back(Point(  1000, -999,  1000));
		points.push_back(Point(  1000, -999, -1000));
		points.push_back(Point( -1000, -999, -1000));
		texs.push_back(Point(.33, .75, 0));
		texs.push_back(Point(.66,   .75, 0));
		texs.push_back(Point(.66,   1, 1));
		texs.push_back(Point(.33, 1, 1));
		texs.push_back(Point(.33, .75, 0));
	}
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		//loadTex("textures/Skybox/skyboxcubemap.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/Skybox/skyboxcubemap.jpg"].textureRef);
		model[model.size()-1].setColor(color[0],color[1],color[2]);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point(-1000, -1000,  999));
		points.push_back(Point(-1000,  1000,  999));
		points.push_back(Point( 1000,  1000,  999));
		points.push_back(Point( 1000, -1000,  999));
		points.push_back(Point(-1000, -1000,  999));
		texs.push_back(Point(1, .5, 0));
		texs.push_back(Point(.66, .5, 0));
		texs.push_back(Point(.66, .25, 0));
		texs.push_back(Point(1, .25, 0));
		texs.push_back(Point(1, .5, 0));
	}
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		//loadTex("textures/Skybox/skyboxcubemap.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/Skybox/skyboxcubemap.jpg"].textureRef);
		model[model.size()-1].setColor(color[0],color[1],color[2]);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point(-1000, -1000, -999));
		points.push_back(Point( 1000, -1000, -999));
		points.push_back(Point( 1000,  1000, -999));
		points.push_back(Point(-1000,  1000, -999));
		points.push_back(Point(-1000, -1000, -999));
		texs.push_back(Point(0, .25, 0));
		texs.push_back(Point(0, .50, 0));
		texs.push_back(Point(.33, .50, 0));
		texs.push_back(Point(.33, .25, 0));
		texs.push_back(Point(0, .25, 0));
	}
}

void Skybox::draw()
{
	glPushAttrib(0xffffffff);
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslated(GLOBAL.CAMERA_POS.x, GLOBAL.CAMERA_POS.y, GLOBAL.CAMERA_POS.z);
	for(int i = 0; i < this->model.size(); i++)
		this->model[i].draw();
	glPopMatrix();
	glPopAttrib();

}

void Skybox::update()
{
	double angle = GLOBAL.CAMERA_ANGLE_VERTICAL;
	double distance, size;
	if(abs(angle) > 45)
	{
		distance = sin(angle/180.0 *PI)*600;
		size = sin(angle/180.0 *PI)*605;
	}
	else
	{
		distance = cos(angle/180.0 *PI)*600;
		size = cos(angle/180.0 *PI)*605;
	}

	if(size < 0)
	{
		size = 0 - size;
		distance = 0 -  distance;
	}
	{
		auto &points = model[0].getPoints();

		points[0] = Point( distance, -size, -size);
		points[1] = Point( distance, -size,  size);
		points[2] = Point( distance,  size,  size);
		points[3] = Point( distance,  size, -size);
		points[4] = Point( distance, -size, -size);
	}
	{
		auto &points = model[1].getPoints();

		points[0] = Point(-distance, -size, -size);
		points[1] = Point(-distance,  size, -size);
		points[2] = Point(-distance,  size,  size);
		points[3] = Point(-distance, -size,  size);
		points[4] = Point(-distance, -size, -size);
	}
	{
		auto &points = model[2].getPoints();

		points[0] = Point(-size,  distance, -size);
		points[1] = Point( size,  distance, -size);
		points[2] = Point( size,  distance,  size);
		points[3] = Point(-size,  distance,  size);
		points[4] = Point(-size,  distance, -size);
	}
	{
		auto &points = model[3].getPoints();

		points[0] = Point(-size, -distance, -size);
		points[1] = Point(-size, -distance,  size);
		points[2] = Point( size, -distance,  size);
		points[3] = Point( size, -distance, -size);
		points[4] = Point(-size, -distance, -size);
	}
	{
		auto &points = model[4].getPoints();

		points[0] = Point(-size, -size,  distance);
		points[1] = Point(-size,  size,  distance);
		points[2] = Point( size,  size,  distance);
		points[3] = Point( size, -size,  distance);
		points[4] = Point(-size, -size,  distance);
	}
	{
		auto &points = model[5].getPoints();

		points[0] = Point(-size, -size, -distance);
		points[1] = Point( size, -size, -distance);
		points[2] = Point( size,  size, -distance);
		points[3] = Point(-size,  size, -distance);
		points[4] = Point(-size, -size, -distance);
	}
}