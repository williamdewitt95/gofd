#include "skybox.h"

Skybox::Skybox()
{
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		loadTex("textures/Skybox/skyboxcubemap.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/Skybox/skyboxcubemap.jpg"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point( 999, -1000, -1000));
		points.push_back(Point( 999, -1000,  1000));
		points.push_back(Point( 999,  1000,  1000));
		points.push_back(Point( 999,  1000, -1000));
		points.push_back(Point( 999, -1000, -1000));
		texs.push_back(Point(0, 0, 0));
		texs.push_back(Point(0, 0, 1));
		texs.push_back(Point(0, 1, 1));
		texs.push_back(Point(0, 1, 0));
		texs.push_back(Point(0, 0, 0));
	}
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		//loadTex("textures/Skybox/skyboxcubemap.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/Skybox/skyboxcubemap.jpg"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point( -999, -1000, -1000));
		points.push_back(Point( -999,  1000, -1000));
		points.push_back(Point( -999,  1000,  1000));
		points.push_back(Point( -999, -1000,  1000));
		points.push_back(Point( -999, -1000, -1000));
		texs.push_back(Point(0, 0, 0));
		texs.push_back(Point(0, 1, 0));
		texs.push_back(Point(0, 1, 1));
		texs.push_back(Point(0, 0, 1));
		texs.push_back(Point(0, 0, 0));
	}
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		//loadTex("textures/Skybox/skyboxcubemap.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/Skybox/skyboxcubemap.jpg"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point( -1000,  999, -1000));
		points.push_back(Point(  1000,  999, -1000));
		points.push_back(Point(  1000,  999,  1000));
		points.push_back(Point( -1000,  999,  1000));
		points.push_back(Point( -1000,  999, -1000));
		texs.push_back(Point(0, 0, 0));
		texs.push_back(Point(0, 0, 1));
		texs.push_back(Point(1, 0, 1));
		texs.push_back(Point(1, 0, 0));
		texs.push_back(Point(0, 0, 0));
	}
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		//loadTex("textures/Skybox/skyboxcubemap.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/Skybox/skyboxcubemap.jpg"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point( -1000, -999, -1000));
		points.push_back(Point( -1000, -999,  1000));
		points.push_back(Point(  1000, -999,  1000));
		points.push_back(Point(  1000, -999, -1000));
		points.push_back(Point( -1000, -999, -1000));
		texs.push_back(Point(0, 0, 0));
		texs.push_back(Point(1, 0, 0));
		texs.push_back(Point(1, 0, 1));
		texs.push_back(Point(0, 0, 1));
		texs.push_back(Point(0, 0, 0));
	}
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		//loadTex("textures/Skybox/skyboxcubemap.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/Skybox/skyboxcubemap.jpg"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point(-1000, -1000,  999));
		points.push_back(Point(-1000,  1000,  999));
		points.push_back(Point( 1000,  1000,  999));
		points.push_back(Point( 1000, -1000,  999));
		points.push_back(Point(-1000, -1000,  999));
		texs.push_back(Point(0, 0, 0));
		texs.push_back(Point(1, 0, 0));
		texs.push_back(Point(1, 1, 0));
		texs.push_back(Point(0, 1, 0));
		texs.push_back(Point(0, 0, 0));
	}
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		//loadTex("textures/Skybox/skyboxcubemap.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/Skybox/skyboxcubemap.jpg"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point(-1000, -1000, -999));
		points.push_back(Point( 1000, -1000, -999));
		points.push_back(Point( 1000,  1000, -999));
		points.push_back(Point(-1000,  1000, -999));
		points.push_back(Point(-1000, -1000, -999));
		texs.push_back(Point(0, 0, 0));
		texs.push_back(Point(0, 1, 0));
		texs.push_back(Point(1, 1, 0));
		texs.push_back(Point(1, 0, 0));
		texs.push_back(Point(0, 0, 0));
	}
}

void Skybox::draw()
{
	glPushMatrix();
	glTranslated(GLOBAL.CAMERA_POS.x, GLOBAL.CAMERA_POS.y, GLOBAL.CAMERA_POS.z);
	for(int i = 0; i < this->model.size(); i++)
	//int i = 0;
		this->model[i].draw();
	glPopMatrix();
	/*i++;
	this->model[i].draw();
	i++;
	glPopMatrix();
	glPushMatrix();
	glTranslated(GLOBAL.CAMERA_POS.x, GLOBAL.CAMERA_POS.y, GLOBAL.CAMERA_POS.z);
	glScaled(scaleFactorSize, scaleFactorDist, scaleFactorSize);
	this->model[i].draw();
	i++;
	this->model[i].draw();
	i++;
	glPopMatrix();
	glPushMatrix();
	glTranslated(GLOBAL.CAMERA_POS.x, GLOBAL.CAMERA_POS.y, GLOBAL.CAMERA_POS.z);
	glScaled(scaleFactorSize, scaleFactorSize, scaleFactorDist);
	this->model[i].draw();
	i++;
	this->model[i].draw();
	glPopMatrix();*/

}

void Skybox::update()
{
	double angle = GLOBAL.CAMERA_ANGLE_VERTICAL;
	double distance, size;
	if(abs(angle) > 45)
	{
		distance = cos(angle/180.0 *PI)*999;
		size = cos(angle/180.0 *PI)*1000;
	}
	else
	{
		distance = sin(angle/180.0 *PI)*999;
		size = sin(angle/180.0 *PI)*1000;
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