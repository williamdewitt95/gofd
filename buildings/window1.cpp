//really all includes should be handledd by things including this file
void makeNewWindow1(const Point &center, double rotation, double height, double width, std::vector<Polygon3d> &model);
unsigned int makeNewWindow1_displayList(const Point &center, double rotation, double height, double width);

unsigned int makeNewWindow1_displayList(const Point &center, double rotation, double height, double width){
	
	std::vector<Polygon3d> model2; // our local copy
	makeNewWindow1(center,rotation,height,width,model2);
	unsigned int list = glGenLists(1);
	glNewList(list,GL_COMPILE);
	for(int x=0;x<model2.size();x++){
		model2[x].draw();
	}
	glEndList();

	return list;
}

void makeNewWindow1(const Point &center, double rotation, double height, double width, std::vector<Polygon3d> &model){
	// center is local from the center-bottom of the building to the center-back of the window
	// rotation is the rotation around Z
	// height is how tall the window itself will be
	// width is how wide the window itself the window will be

	double depth = 0.25; // how far out the pieces come off the wall
	double depth_bottom = 0.5; // how far the bottom piece comes off the wall - typically is thicker
	double thickness = 0.2; //how thick all the sides are

	Vector rot(0,0,rotation);

	// === Pane Of Glass ===
	{
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		// loadTex("textures/white.png");
		// model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/white.png"].textureRef);
		model[model.size()-1].setColor(100,100,255);
		model[model.size()-1].setTesselation(true);
		model[model.size()-1].setRotation(rot);
		model[model.size()-1].setCenter(center);

		points.push_back(Point(  -width/2.0, -0.05 ,  height/2.0));
		points.push_back(Point(  -width/2.0, -0.05 , -height/2.0));
		points.push_back(Point(   width/2.0, -0.05 , -height/2.0));
		points.push_back(Point(   width/2.0, -0.05 ,  height/2.0));
		points.push_back(Point(  -width/2.0, -0.05 ,  height/2.0));
		texs.push_back(Point( 0 , 0 , 0 ));
		texs.push_back(Point( 0 , 1 , 0 ));
		texs.push_back(Point( 1 , 1 , 0 ));
		texs.push_back(Point( 1 , 0 , 0 ));
		texs.push_back(Point( 0 , 0 , 0 ));
	}



	{ // bottom self bottom
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		// loadTex("textures/white.png");
		// model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/white.png"].textureRef);
		model[model.size()-1].setColor(255,50,50);
		model[model.size()-1].setTesselation(true);
		model[model.size()-1].setRotation(rot);
		model[model.size()-1].setCenter(center);

		points.push_back(Point(  -width/2.0 , -depth_bottom , -height/2.0));
		points.push_back(Point(  -width/2.0 ,        0      , -height/2.0));
		points.push_back(Point(   width/2.0 ,        0      , -height/2.0));
		points.push_back(Point(   width/2.0 , -depth_bottom , -height/2.0));
		points.push_back(Point(  -width/2.0 , -depth_bottom , -height/2.0));
		texs.push_back(Point( 0 , 0 , 0 ));
		texs.push_back(Point( 0 , 1 , 0 ));
		texs.push_back(Point( 1 , 1 , 0 ));
		texs.push_back(Point( 1 , 0 , 0 ));
		texs.push_back(Point( 0 , 0 , 0 ));
	}
	{ // bottom self top
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		// loadTex("textures/white.png");
		// model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/white.png"].textureRef);
		model[model.size()-1].setColor(255,50,50);
		model[model.size()-1].setTesselation(true);
		model[model.size()-1].setRotation(rot);
		model[model.size()-1].setCenter(center);

		points.push_back(Point(  -width/2.0 + thickness ,        0      , -height/2.0 + thickness));
		points.push_back(Point(  -width/2.0 + thickness , -depth_bottom , -height/2.0 + thickness));
		points.push_back(Point(   width/2.0 - thickness , -depth_bottom , -height/2.0 + thickness));
		points.push_back(Point(   width/2.0 - thickness ,        0      , -height/2.0 + thickness));
		points.push_back(Point(  -width/2.0 + thickness ,        0      , -height/2.0 + thickness));
		texs.push_back(Point( 0 , 0 , 0 ));
		texs.push_back(Point( 0 , 1 , 0 ));
		texs.push_back(Point( 1 , 1 , 0 ));
		texs.push_back(Point( 1 , 0 , 0 ));
		texs.push_back(Point( 0 , 0 , 0 ));
	}
	{ // bottom self front
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		// loadTex("textures/white.png");
		// model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/white.png"].textureRef);
		model[model.size()-1].setColor(255,50,50);
		model[model.size()-1].setTesselation(true);
		model[model.size()-1].setRotation(rot);
		model[model.size()-1].setCenter(center);

		points.push_back(Point(  -width/2.0 + thickness , -depth_bottom , -height/2.0 + thickness));
		points.push_back(Point(  -width/2.0             , -depth_bottom , -height/2.0            ));
		points.push_back(Point(   width/2.0             , -depth_bottom , -height/2.0            ));
		points.push_back(Point(   width/2.0 - thickness , -depth_bottom , -height/2.0 + thickness));
		points.push_back(Point(  -width/2.0 + thickness , -depth_bottom , -height/2.0 + thickness));
		texs.push_back(Point( 0 , 0 , 0 ));
		texs.push_back(Point( 0 , 1 , 0 ));
		texs.push_back(Point( 1 , 1 , 0 ));
		texs.push_back(Point( 1 , 0 , 0 ));
		texs.push_back(Point( 0 , 0 , 0 ));
	}
	{ // bottom self leftSide
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		// loadTex("textures/white.png");
		// model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/white.png"].textureRef);
		model[model.size()-1].setColor(255,50,50);
		model[model.size()-1].setTesselation(true);
		model[model.size()-1].setRotation(rot);
		model[model.size()-1].setCenter(center);

		points.push_back(Point(  -width/2.0 + thickness ,        0      , -height/2.0 + thickness));
		points.push_back(Point(  -width/2.0             ,        0      , -height/2.0            ));
		points.push_back(Point(  -width/2.0             , -depth_bottom , -height/2.0            ));
		points.push_back(Point(  -width/2.0 + thickness , -depth_bottom , -height/2.0 + thickness));
		points.push_back(Point(  -width/2.0 + thickness ,        0      , -height/2.0 + thickness));
		texs.push_back(Point( 0 , 0 , 0 ));
		texs.push_back(Point( 0 , 1 , 0 ));
		texs.push_back(Point( 1 , 1 , 0 ));
		texs.push_back(Point( 1 , 0 , 0 ));
		texs.push_back(Point( 0 , 0 , 0 ));
	}
	{ // bottom self rightSide
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		// loadTex("textures/white.png");
		// model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/white.png"].textureRef);
		model[model.size()-1].setColor(255,50,50);
		model[model.size()-1].setTesselation(true);
		model[model.size()-1].setRotation(rot);
		model[model.size()-1].setCenter(center);

		points.push_back(Point(  width/2.0 - thickness , -depth_bottom , -height/2.0 + thickness));
		points.push_back(Point(  width/2.0             , -depth_bottom , -height/2.0            ));
		points.push_back(Point(  width/2.0             ,        0      , -height/2.0            ));
		points.push_back(Point(  width/2.0 - thickness ,        0      , -height/2.0 + thickness));
		points.push_back(Point(  width/2.0 - thickness , -depth_bottom , -height/2.0 + thickness));
		texs.push_back(Point( 0 , 0 , 0 ));
		texs.push_back(Point( 0 , 1 , 0 ));
		texs.push_back(Point( 1 , 1 , 0 ));
		texs.push_back(Point( 1 , 0 , 0 ));
		texs.push_back(Point( 0 , 0 , 0 ));
	}



	{ // left border leftSide
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		// loadTex("textures/white.png");
		// model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/white.png"].textureRef);
		model[model.size()-1].setColor(50,175,50);
		model[model.size()-1].setTesselation(true);
		model[model.size()-1].setRotation(rot);
		model[model.size()-1].setCenter(center);

		points.push_back(Point(  -width/2.0 ,    0   ,  height/2.0 ));
		points.push_back(Point(  -width/2.0 ,    0   , -height/2.0 ));
		points.push_back(Point(  -width/2.0 , -depth , -height/2.0 ));
		points.push_back(Point(  -width/2.0 , -depth ,  height/2.0 ));
		points.push_back(Point(  -width/2.0 ,    0   ,  height/2.0 ));
		texs.push_back(Point( 0 , 0 , 0 ));
		texs.push_back(Point( 0 , 1 , 0 ));
		texs.push_back(Point( 1 , 1 , 0 ));
		texs.push_back(Point( 1 , 0 , 0 ));
		texs.push_back(Point( 0 , 0 , 0 ));
	}
	{ // left border rightSide
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		// loadTex("textures/white.png");
		// model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/white.png"].textureRef);
		model[model.size()-1].setColor(50,175,50);
		model[model.size()-1].setTesselation(true);
		model[model.size()-1].setRotation(rot);
		model[model.size()-1].setCenter(center);

		points.push_back(Point(  -width/2.0 + thickness , -depth ,  height/2.0 - thickness ));
		points.push_back(Point(  -width/2.0 + thickness , -depth , -height/2.0 + thickness ));
		points.push_back(Point(  -width/2.0 + thickness ,    0   , -height/2.0 + thickness ));
		points.push_back(Point(  -width/2.0 + thickness ,    0   ,  height/2.0 - thickness ));
		points.push_back(Point(  -width/2.0 + thickness , -depth ,  height/2.0 - thickness ));
		texs.push_back(Point( 0 , 0 , 0 ));
		texs.push_back(Point( 0 , 1 , 0 ));
		texs.push_back(Point( 1 , 1 , 0 ));
		texs.push_back(Point( 1 , 0 , 0 ));
		texs.push_back(Point( 0 , 0 , 0 ));
	}
	{ // left border front
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		// loadTex("textures/white.png");
		// model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/white.png"].textureRef);
		model[model.size()-1].setColor(50,175,50);
		model[model.size()-1].setTesselation(true);
		model[model.size()-1].setRotation(rot);
		model[model.size()-1].setCenter(center);

		points.push_back(Point(  -width/2.0             , -depth ,  height/2.0             ));
		points.push_back(Point(  -width/2.0             , -depth , -height/2.0             ));
		points.push_back(Point(  -width/2.0 + thickness , -depth , -height/2.0 + thickness ));
		points.push_back(Point(  -width/2.0 + thickness , -depth ,  height/2.0 - thickness ));
		points.push_back(Point(  -width/2.0             , -depth ,  height/2.0             ));
		texs.push_back(Point( 0 , 0 , 0 ));
		texs.push_back(Point( 0 , 1 , 0 ));
		texs.push_back(Point( 1 , 1 , 0 ));
		texs.push_back(Point( 1 , 0 , 0 ));
		texs.push_back(Point( 0 , 0 , 0 ));
	}



	{ // right border rightSide
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		// loadTex("textures/white.png");
		// model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/white.png"].textureRef);
		model[model.size()-1].setColor(50,175,50);
		model[model.size()-1].setTesselation(true);
		model[model.size()-1].setRotation(rot);
		model[model.size()-1].setCenter(center);

		points.push_back(Point(  width/2.0 , -depth ,  height/2.0 ));
		points.push_back(Point(  width/2.0 , -depth , -height/2.0 ));
		points.push_back(Point(  width/2.0 ,    0   , -height/2.0 ));
		points.push_back(Point(  width/2.0 ,    0   ,  height/2.0 ));
		points.push_back(Point(  width/2.0 , -depth ,  height/2.0 ));
		texs.push_back(Point( 0 , 0 , 0 ));
		texs.push_back(Point( 0 , 1 , 0 ));
		texs.push_back(Point( 1 , 1 , 0 ));
		texs.push_back(Point( 1 , 0 , 0 ));
		texs.push_back(Point( 0 , 0 , 0 ));
	}
	{ // right border leftSide
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		// loadTex("textures/white.png");
		// model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/white.png"].textureRef);
		model[model.size()-1].setColor(50,175,50);
		model[model.size()-1].setTesselation(true);
		model[model.size()-1].setRotation(rot);
		model[model.size()-1].setCenter(center);

		points.push_back(Point(  width/2.0 - thickness ,    0   ,  height/2.0 - thickness ));
		points.push_back(Point(  width/2.0 - thickness ,    0   , -height/2.0 + thickness ));
		points.push_back(Point(  width/2.0 - thickness , -depth , -height/2.0 + thickness ));
		points.push_back(Point(  width/2.0 - thickness , -depth ,  height/2.0 - thickness ));
		points.push_back(Point(  width/2.0 - thickness ,    0   ,  height/2.0 - thickness ));
		texs.push_back(Point( 0 , 0 , 0 ));
		texs.push_back(Point( 0 , 1 , 0 ));
		texs.push_back(Point( 1 , 1 , 0 ));
		texs.push_back(Point( 1 , 0 , 0 ));
		texs.push_back(Point( 0 , 0 , 0 ));
	}
	{ // right border front
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		// loadTex("textures/white.png");
		// model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/white.png"].textureRef);
		model[model.size()-1].setColor(50,175,50);
		model[model.size()-1].setTesselation(true);
		model[model.size()-1].setRotation(rot);
		model[model.size()-1].setCenter(center);

		points.push_back(Point(  width/2.0 - thickness , -depth ,  height/2.0 - thickness ));
		points.push_back(Point(  width/2.0 - thickness , -depth , -height/2.0 + thickness ));
		points.push_back(Point(  width/2.0             , -depth , -height/2.0             ));
		points.push_back(Point(  width/2.0             , -depth ,  height/2.0             ));
		points.push_back(Point(  width/2.0 - thickness , -depth ,  height/2.0 - thickness ));
		texs.push_back(Point( 0 , 0 , 0 ));
		texs.push_back(Point( 0 , 1 , 0 ));
		texs.push_back(Point( 1 , 1 , 0 ));
		texs.push_back(Point( 1 , 0 , 0 ));
		texs.push_back(Point( 0 , 0 , 0 ));
	}

	{ // top border topSide
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		// loadTex("textures/white.png");
		// model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/white.png"].textureRef);
		model[model.size()-1].setColor(50,50,175);
		model[model.size()-1].setTesselation(true);
		model[model.size()-1].setRotation(rot);
		model[model.size()-1].setCenter(center);

		points.push_back(Point( -width/2.0 ,    0   ,  height/2.0 ));
		points.push_back(Point( -width/2.0 , -depth ,  height/2.0 ));
		points.push_back(Point(  width/2.0 , -depth ,  height/2.0 ));
		points.push_back(Point(  width/2.0 ,    0   ,  height/2.0 ));
		points.push_back(Point( -width/2.0 ,    0   ,  height/2.0 ));
		texs.push_back(Point( 0 , 0 , 0 ));
		texs.push_back(Point( 0 , 1 , 0 ));
		texs.push_back(Point( 1 , 1 , 0 ));
		texs.push_back(Point( 1 , 0 , 0 ));
		texs.push_back(Point( 0 , 0 , 0 ));
	}
	{ // top border bottomSide
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		// loadTex("textures/white.png");
		// model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/white.png"].textureRef);
		model[model.size()-1].setColor(50,50,175);
		model[model.size()-1].setTesselation(true);
		model[model.size()-1].setRotation(rot);
		model[model.size()-1].setCenter(center);

		points.push_back(Point( -width/2.0 + thickness , -depth ,  height/2.0 - thickness ));
		points.push_back(Point( -width/2.0 + thickness ,    0   ,  height/2.0 - thickness ));
		points.push_back(Point(  width/2.0 - thickness ,    0   ,  height/2.0 - thickness ));
		points.push_back(Point(  width/2.0 - thickness , -depth ,  height/2.0 - thickness ));
		points.push_back(Point( -width/2.0 + thickness , -depth ,  height/2.0 - thickness ));
		texs.push_back(Point( 0 , 0 , 0 ));
		texs.push_back(Point( 0 , 1 , 0 ));
		texs.push_back(Point( 1 , 1 , 0 ));
		texs.push_back(Point( 1 , 0 , 0 ));
		texs.push_back(Point( 0 , 0 , 0 ));
	}
	{ // top border front
		model.push_back(Polygon3d());
		auto &points = model[model.size()-1].getPoints();
		auto &texs = model[model.size()-1].getTexturePoints();
		// loadTex("textures/white.png");
		// model[model.size()-1].setTexture(GLOBAL.TEXTURES_LOADED["textures/white.png"].textureRef);
		model[model.size()-1].setColor(50,50,175);
		model[model.size()-1].setTesselation(true);
		model[model.size()-1].setRotation(rot);
		model[model.size()-1].setCenter(center);

		points.push_back(Point( -width/2.0             , -depth , height/2.0             ));
		points.push_back(Point( -width/2.0 + thickness , -depth , height/2.0 - thickness ));
		points.push_back(Point(  width/2.0 - thickness , -depth , height/2.0 - thickness ));
		points.push_back(Point(  width/2.0             , -depth , height/2.0             ));
		points.push_back(Point( -width/2.0             , -depth , height/2.0             ));
		texs.push_back(Point( 0 , 0 , 0 ));
		texs.push_back(Point( 0 , 1 , 0 ));
		texs.push_back(Point( 1 , 1 , 0 ));
		texs.push_back(Point( 1 , 0 , 0 ));
		texs.push_back(Point( 0 , 0 , 0 ));
	}
}