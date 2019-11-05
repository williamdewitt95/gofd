#include "engine/polygon3d.h"

Polygon3d::Polygon3d(){
	color[0]=0;
	color[1]=0;
	color[2]=0;
	color[3]=0;
	scale = 1;
	maxRadius = 0;
	hasTex = false;
}

Polygon3d::Polygon3d(double x,double y,double z){
	this->center = Point(x,y,z);

	color[0]=0;
	color[1]=0;
	color[2]=0;
	color[3]=0;
	scale = 1;
	maxRadius = 0;
	hasTex = false;
}
Polygon3d::Polygon3d(std::vector<Point>& points){
	this->vertexList = points;

	color[0]=0;
	color[1]=0;
	color[2]=0;
	color[3]=0;
	scale = 1;
	maxRadius = 0;
	hasTex = false;
}

Polygon3d::Polygon3d(Point pnt, std::vector<Point>& points){

	this->center = pnt;
	this->vertexList = points;

	color[0]=0;
	color[1]=0;
	color[2]=0;
	color[3]=0;
	scale = 1;
	maxRadius = 0;
	hasTex = false;

}

Polygon3d::Polygon3d(Triangle &tri){
	color[0]=0;
	color[1]=0;
	color[2]=0;
	color[3]=0;
	scale = 1;
	maxRadius = 0;
	hasTex = false;

	this->vertexList.push_back(tri.p1);
	this->vertexList.push_back(tri.p2);
	this->vertexList.push_back(tri.p3);
}
Polygon3d::Polygon3d(const Polygon3d& other){
	this->center = other.center;
	this->rotation=other.rotation;
	this->scale=other.scale;
	for(int x=0;x<4;x++)this->color[x] = other.color[x];
	this->normal = other.normal;

	this->vertexList=other.vertexList;

	this->maxRadius = 0;

	this->texture = other.texture;
	this->hasTex = other.hasTex;
	this->vertexTextureList = other.vertexTextureList;
}

void Polygon3d::setRotation(Vector& rot){
	this->rotation=rot;
}
Vector Polygon3d::getRotation(){
	return this->rotation;
}
void Polygon3d::setScale(double& sc){
	this->scale = sc;
}
double Polygon3d::getScale(){
	return this->scale;
}
void Polygon3d::setCenter(Point& pp){
	this->center = pp;
}
Point Polygon3d::getCenter(){
	return this->center;
}
void Polygon3d::setColor(GLubyte& red,GLubyte& green, GLubyte& blue){
	this->color[0]=red;
	this->color[1]=green;
	this->color[2]=blue;
	this->color[3]=255;
}
void Polygon3d::setColor(GLubyte& red,GLubyte& green, GLubyte& blue, GLubyte& alpha){
	this->color[0]=red;
	this->color[1]=green;
	this->color[2]=blue;
	this->color[3]=alpha;
}
GLubyte Polygon3d::getColor(int& channel){
	return this->color[channel];
}
double Polygon3d::getMaxRadius(){
	if(this->maxRadius == 0){
		//we are going to calculate the max distance from our center
		//this lets us remove a lot of excess calculations for polygons that are just too far away
		for(int x=0; x<this->numPoints(); x++){
			double temp=0;
			temp += pow(this->vertexList[x].x,2);
			temp += pow(this->vertexList[x].y,2);
			temp += pow(this->vertexList[x].z,2);
			temp = sqrt(temp);

			if(temp > this->maxRadius) this->maxRadius = temp;
		}
	}
	return this->maxRadius;
}
void Polygon3d::setNormal(Vector& norm){
	this->normal = norm;
}
void Polygon3d::calculateNormal(){
	if (this->vertexList.size() < 3 ) return; // not enough points to calculate a normal
	std::vector<Point> worldPoints = getTransform().getPoints();
	this->normal = Vector(worldPoints.at(0),worldPoints.at(1)).cross(Vector(worldPoints.at(1),worldPoints.at(2)));
}
Vector Polygon3d::getNormal(){
	if ( this->normal.x == 0 && normal.y == 0 && normal.z == 0 ){
		this->calculateNormal();
	}
	return this->normal;
}

void Polygon3d::setTexture(std::string& tex){
	this->texture = tex;
	this->hasTex=true;
}
std::string Polygon3d::getTexture(){
	return this->texture;
}
std::vector<Point>& Polygon3d::getTexturePoints(){
	return this->vertexTextureList;
}
Point& Polygon3d::getTexturePos(int index){
	return this->vertexTextureList[index];
}
bool Polygon3d::hasTexture(){
	return this->hasTex;
}
void Polygon3d::removeTexture(){
	this->hasTex=false;
}

int Polygon3d::numPoints()const{
	return this->vertexList.size();
}
std::vector<Point>& Polygon3d::getPoints(){
	return this->vertexList;
}
Point& Polygon3d::operator[](int x){
	return this->vertexList[x];
}
Polygon3d& Polygon3d::operator=(Polygon3d other){

	this->center = other.center;
	this->rotation = other.rotation;
	this->scale = other.scale;
	for(int x=0;x<4;x++)this->color[x] = other.color[x];
	this->normal = other.normal;

	this->vertexList = other.vertexList;

	this->maxRadius=0; // special little optimization for collision checking

	this->texture = other.texture;
	this->hasTex = other.hasTex;
	this->vertexTextureList = other.vertexTextureList;
	
	return *this;
}


Polygon3d Polygon3d::getTransform(){ // get the transform of the points of the polygon to where they should be
	Polygon3d poly(*this);
	std::vector<Point> &worldCoords = poly.getPoints();

	for(auto& p : worldCoords){
		p = p
		    .rotatePoint(poly.rotation.x, 1, 0, 0 )
		    .rotatePoint(poly.rotation.y, 0, 1, 0 )
		    .rotatePoint(poly.rotation.z, 0, 0, 1 )		
		    .translatePoint(poly.center[0], poly.center[1], poly.center[2])
		    .scalePoint(poly.scale, poly.scale, poly.scale);
	}	

	return poly;
}




// void Polygon3d::draw(){
// 	if(this->numPoints()<2)return;

// 	glColor4ub(this->color[0],this->color[1],this->color[2],this->color[3]);
		
// 	glPushMatrix();
// 	//translate
// 	glTranslated(this->center[0],this->center[1],this->center[2]);
// 	//scale
// 	glScaled(this->scale,this->scale,this->scale);
// 	//rotate
// 	glRotated(this->rotation.x,1,0,0);
// 	glRotated(this->rotation.y,0,1,0);
// 	glRotated(this->rotation.z,0,0,1);

// 	//set the normal of the plane
// 	Vector normal = Vector(vertexList[0],vertexList[1]).cross(Vector(vertexList[1],vertexList[2]));
// 	glNormal3d(normal.x,normal.y,normal.z);
// 	// glBegin(GL_LINES); // debug to show the normal of each plane
// 	// glVertex3d(0,0,0);
// 	// glVertex3d(normal.x,normal.y,normal.z);
// 	// glEnd();
// 	if(this->hasTexture()){
// 		glBindTexture(GL_TEXTURE_2D,this->getTexture());
// 	}

// 	GLUtesselator* tessObj = gluNewTess();

// 	if(tessObj == NULL) return; // encountered an error and so we are done
// 	if(this->drawTesselate){
// 		gluTessProperty(tessObj,GLU_TESS_BOUNDARY_ONLY,GL_FALSE); // dont only draw the outer edges but the whole interior
// 	}else{
// 		gluTessProperty(tessObj,GLU_TESS_BOUNDARY_ONLY,GL_TRUE); // only draw the outer edges
// 	}
// 	gluTessCallback(tessObj, GLU_TESS_BEGIN, (void(*)())glBegin);
// 	// gluTessCallback(tessObj, GLU_TESS_VERTEX, (void(*)())glVertex3dv);
// 	gluTessCallback(tessObj, GLU_TESS_VERTEX_DATA, (void(*)())__secretVertexDrawingFunction);
// 	gluTessCallback(tessObj, GLU_TESS_END, (void(*)())glEnd);

// 	//add our points in to the object to be tesselated
// 	gluTessBeginPolygon(tessObj,this); // start tesselating and have it able to hand us a pointer to this object
// 		gluTessBeginContour(tessObj);
// 			for(long x=0;x<this->vertexList.size()-1;x++){
// 				gluTessVertex(tessObj,(double*)&this->vertexList[x],(long*)x); // give the tesselator a point and give us an index to the pixel
// 				// gluTessVertex(tessObj,(double*)&this->vertexList[x],(double*)&this->vertexList[x]);
// 			}
// 		gluTessEndContour(tessObj);
// 	gluTessEndPolygon(tessObj);

// 	gluDeleteTess(tessObj);

// 	if(this->hasTexture()){
// 		//reset to the default empty texture
// 		glBindTexture(GL_TEXTURE_2D, 0);
// 	}

// 	glPopMatrix();
// }
// void Polygon3d::drawLines(){
// 	//remember what it was before
// 	auto temp = this->drawTesselate;

// 	this->drawTesselate=false;
// 	this->draw();

// 	//put it back to the way it was before
// 	this->drawTesselate = temp;
// }
// void Polygon3d::draw_static(){
// 	if(this->numPoints()<2)return;

// 	glColor4ub(this->color[0],this->color[1],this->color[2],this->color[3]);
		
// 	//set the normal of the plane
// 	Vector normal = Vector(vertexList[0],vertexList[1]).cross(Vector(vertexList[1],vertexList[2]));
// 	glNormal3d(normal.x,normal.y,normal.z);
// 	// glBegin(GL_LINES); // debug to show the normal of each plane
// 	// glVertex3d(0,0,0);
// 	// glVertex3d(normal.x,normal.y,normal.z);
// 	// glEnd();
// 	if(this->hasTexture()){
// 		glBindTexture(GL_TEXTURE_2D,this->getTexture());
// 	}

// 	GLUtesselator* tessObj = gluNewTess();

// 	if(tessObj == NULL) return; // encountered an error and so we are done
// 	if(this->drawTesselate){
// 		gluTessProperty(tessObj,GLU_TESS_BOUNDARY_ONLY,GL_FALSE); // dont only draw the outer edges but the whole interior
// 	}else{
// 		gluTessProperty(tessObj,GLU_TESS_BOUNDARY_ONLY,GL_TRUE); // only draw the outer edges
// 	}
// 	gluTessCallback(tessObj, GLU_TESS_BEGIN, (void(*)())glBegin);
// 	// gluTessCallback(tessObj, GLU_TESS_VERTEX, (void(*)())glVertex3dv);
// 	gluTessCallback(tessObj, GLU_TESS_VERTEX_DATA, (void(*)())__secretVertexDrawingFunction);
// 	gluTessCallback(tessObj, GLU_TESS_END, (void(*)())glEnd);

// 	//add our points in to the object to be tesselated
// 	gluTessBeginPolygon(tessObj,this); // start tesselating and have it able to hand us a pointer to this object
// 		gluTessBeginContour(tessObj);
// 			for(long x=0;x<this->vertexList.size()-1;x++){
// 				gluTessVertex(tessObj,(double*)&this->vertexList[x],(long*)x); // give the tesselator a point and give us an index to the pixel
// 				// gluTessVertex(tessObj,(double*)&this->vertexList[x],(double*)&this->vertexList[x]);
// 			}
// 		gluTessEndContour(tessObj);
// 	gluTessEndPolygon(tessObj);

// 	gluDeleteTess(tessObj);

// 	if(this->hasTexture()){
// 		//reset to the default empty texture
// 		glBindTexture(GL_TEXTURE_2D, 0);
// 	}
// }
// void Polygon3d::__secretVertexDrawingFunction(void *data, void *polygon){
// 	//for every vertex made by the tesselator, we get called here
// 	//we are passed 2 things
// 	// - data which is really just and int in disguise
// 	// - pointer to the polygon being tesselated
// 	//we use the int as the index to the vertex being drawn
// 	//we use the polygon to get the position of the vertex

// 	long index = (long)data;
// 	Polygon3d* poly=(Polygon3d*)polygon;
// 	if(poly->hasTexture() && poly->getTesselation()){
// 		Point& p = poly->getTexturePos(index);
// 		glTexCoord2d(p.x,p.y);
// 	}
// 	glVertex3dv((double*)&(*poly)[index]);
// }
// void Polygon3d::update(){
// 	this->center += this->velocity;
// 	this->rotation += this->rotationSpeed;
// }
