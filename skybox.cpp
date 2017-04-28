#include "skybox.h"

Skybox::Skybox(Point cameraCenter)
{
	this->center = cameraCenter;
	{
        model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		loadTex("textures/Skybox/skyboxcubemap.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/Skybox/skyboxcubemap.jpg"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point( 2000, -2000, -2000));
		points.push_back(Point( 2000, -2000,  2000));
		points.push_back(Point( 2000,  2000,  2000));
		points.push_back(Point( 2000,  2000, -2000));
		points.push_back(Point( 2000, -2000, -2000));
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
		loadTex("textures/Skybox/skyboxcubemap.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/Skybox/skyboxcubemap.jpg"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point( -2000, -2000, -2000));
		points.push_back(Point( -2000,  2000, -2000));
		points.push_back(Point( -2000,  2000,  2000));
		points.push_back(Point( -2000, -2000,  2000));
		points.push_back(Point( -2000, -2000, -2000));
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
		loadTex("textures/Skybox/skyboxcubemap.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/Skybox/skyboxcubemap.jpg"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point( -2000,  2000, -2000));
		points.push_back(Point( -2000,  2000,  2000));
		points.push_back(Point(  2000,  2000,  2000));
		points.push_back(Point(  2000,  2000, -2000));
		points.push_back(Point( -2000,  2000, -2000));
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
		loadTex("textures/Skybox/skyboxcubemap.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/Skybox/skyboxcubemap.jpg"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point( -2000, -2000, -2000));
		points.push_back(Point(  2000, -2000, -2000));
		points.push_back(Point(  2000, -2000,  2000));
		points.push_back(Point( -2000, -2000,  2000));
		points.push_back(Point( -2000, -2000, -2000));
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
		loadTex("textures/Skybox/skyboxcubemap.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/Skybox/skyboxcubemap.jpg"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point(-2000, -2000,  2000));
		points.push_back(Point( 2000, -2000,  2000));
		points.push_back(Point( 2000,  2000,  2000));
		points.push_back(Point(-2000,  2000,  2000));
		points.push_back(Point(-2000, -2000,  2000));
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
		loadTex("textures/Skybox/skyboxcubemap.jpg");
		model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/Skybox/skyboxcubemap.jpg"].textureRef);
		model[model.size()-1].setColor(255,255,255);
		model[model.size()-1].setTesselation(true);

		points.push_back(Point(-2000, -2000,  2000));
		points.push_back(Point(-2000,  2000,  2000));
		points.push_back(Point( 2000,  2000,  2000));
		points.push_back(Point( 2000, -2000,  2000));
		points.push_back(Point(-2000, -2000,  2000));
		texs.push_back(Point(0, 0, 0));
		texs.push_back(Point(0, 1, 0));
		texs.push_back(Point(1, 1, 0));
		texs.push_back(Point(1, 0, 0));
		texs.push_back(Point(0, 0, 0));
	}
}

void Skybox::draw(Point cameraCenter)
{
	glPushMatrix();

	glTranslate(GLOBAL.CAMERA_POS.x, GLOBAL.CAMERA_POS.y, GLOBAL.CAMERA_POS.z);
	for(int i = 0; i < this->model.size(); i++)
		this->model[x].draw();
	glPopmatrix();
}