#include "vector_basics.h"


//==============================================================================
// POINT CLASS
//==============================================================================
// Handles keeping the x,y,z of a single point and integrates with vectors
//==============================================================================
Point::Point(){
	this->x=0;this->y=0;this->z=0;
}
Point::Point(double x, double y, double z){
	this->x = x;
	this->y = y;
	this->z = z;
}

//==============================================================================
//  OPERATOR OVERLOADS
//==============================================================================
Point& Point::operator+=(const Vector& other){
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}
Point& Point::operator+=(const Point& other){
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}
Point Point::operator+(const Vector& other){
	Point pp;
	pp.x = this->x + other.x;
	pp.y = this->y + other.y;
	pp.z = this->z + other.z;
	return pp; 
}
Point Point::operator+(const Point& other){
	Point pp;
	pp.x = this->x + other.x;
	pp.y = this->y + other.y;
	pp.z = this->z + other.z;
	return pp; 
}
Point& Point::operator*=(const double scale){
	this->x *= scale;
	this->y *= scale;
	this->z *= scale;
	return *this;
}
Point Point::operator*(const double scale){
	Point pp;
	pp.x = this->x * scale;
	pp.y = this->y * scale;
	pp.z = this->z * scale;
	return pp;
}
Point& Point::operator/=(const double scale){
	this->x /= scale;
	this->y /= scale;
	this->z /= scale;
	return *this;
}
Point Point::operator/(const double scale){
	Point pp;
	pp.x = this->x / scale;
	pp.y = this->y / scale;
	pp.z = this->z / scale;
	return pp;
}
bool Point::operator==(const Point& other){
	return
		this->x == other.x &&
		this->y == other.y &&
		this->z == other.z;
}
bool Point::operator!=(const Point& other){
	return !(this->operator==(other));
}
double& Point::operator[](const int index){
	return this->data[index];
}

Point Point::translatePoint(double x, double y, double z){

	Point pnt; 

	pnt.x = x;
	pnt.y = y;
	pnt.z = z;

	*this += pnt;	  
	
	return *this;

}

Point Point::scalePoint(double scaleX, double scaleY, double scaleZ){
	
	this->x *= scaleX;
	this->y *= scaleY;
	this->z *= scaleZ; 

	return *this;
}

Point Point::rotatePoint(double theta, bool x, bool y, bool z){

	float phi = theta * M_PI / 180.0;

	double tMat[4][4];


	if(x){
		// std::cout << "rotate x " << theta << std::endl;
		tMat[0][0] = 1.0;		tMat[0][1] = 0.0;		tMat[0][2] = 0.0;       tMat[0][3] = 0.0;
        tMat[1][0] = 0.0;		tMat[1][1] = cos(phi);  tMat[1][2] = sin(phi);  tMat[1][3] = 0.0;
        tMat[2][0] = 0.0;       tMat[2][1] = -sin(phi); tMat[2][2] = cos(phi);  tMat[2][3] = 0.0;
        tMat[3][0] = 0.0;       tMat[3][1] = 0.0;       tMat[3][2] = 0.0;       tMat[3][3] = 1.0;
			

	}

	else if (y){
		// std::cout << "rotate y " << theta << std::endl;
		tMat[0][0] = cos(phi);  tMat[0][1] = 0.0;       tMat[0][2] =-sin(phi);  tMat[0][3] = 0.0;
        tMat[1][0] = 0.0;  		tMat[1][1] = 1.0;  		tMat[1][2] = 0.0;       tMat[1][3] = 0.0;
        tMat[2][0] = sin(phi);  tMat[2][1] = 0.0;       tMat[2][2] = cos(phi);  tMat[2][3] = 0.0;
        tMat[3][0] = 0.0;       tMat[3][1] = 0.0;       tMat[3][2] = 0.0;       tMat[3][3] = 1.0;
	}

	else if (z){
		// std::cout << "rotate z " << theta << std::endl;
		tMat[0][0] = cos(phi);	tMat[0][1] =-sin(phi);  tMat[0][2] = 0.0;		tMat[0][3] = 0.0;
		tMat[1][0] = sin(phi);	tMat[1][1] = cos(phi);  tMat[1][2] = 0.0;		tMat[1][3] = 0.0;
		tMat[2][0] = 0.0;		tMat[2][1] = 0.0;		tMat[2][2] = 1.0; 		tMat[2][3] = 0.0;
		tMat[3][0] = 0.0;		tMat[3][1] = 0.0;		tMat[3][2] = 0.0;		tMat[3][3] = 1.0;
	}

	Point tmp;
	//tmp->x = 0, tmp->y = 0, tmp->z = 0;

	tmp.x = this->x*tMat[0][0] + this->y*tMat[0][1] + this->z*tMat[0][2]; 
	tmp.y = this->x*tMat[1][0] + this->y*tMat[1][1] + this->z*tMat[1][2];
	tmp.z = this->x*tMat[2][0] + this->y*tMat[2][1] + this->z*tMat[2][2];

	return tmp; 
	

}

//==============================================================================
// VECTOR CLASS
//==============================================================================
// Handles keeping the x,y,z of a vector, does basic vector math, and
// integrates with points a little
//==============================================================================
Vector::Vector(){
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
Vector::Vector(double x, double y, double z){
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector::Vector(Point& p1, Point& p2){ // p1 is the starting point and p2 is where we are going
	this->x = p2.x - p1.x;
	this->y = p2.y - p1.y;
	this->z = p2.z - p1.z;
}

//==============================================================================
//  BASIC VECTOR OPERATIONS
//==============================================================================
double Vector::magnitude(){
	double temp = (this->x*this->x) + (this->y*this->y) + (this->z*this->z);
	if( temp <= 0){
		printf("FREAK OUT - THE SQRT IS GETTING A NEGATIVE NUMBER\n\t%lf\n",temp);
	}
	temp = sqrt(temp);
	return temp;
}
double Vector::length(){
	return this->magnitude();
}
double Vector::dot(Vector& other){
	return
		this->x * other.x +
		this->y * other.y +
		this->z * other.z;
}
double Vector::dotProduct(Vector& other){
	this->dot(other);
}
Vector Vector::cross(const Vector& other){
	Vector pp;
	pp.x = (this->y*other.z) - (this->z*other.y);
	pp.y = (this->z*other.x) - (this->x*other.z);
	pp.z = (this->x*other.y) - (this->y*other.x);
	return pp;
}
Vector Vector::crossProduct(Vector& other){
	this->cross(other);
}

//==============================================================================
//  OPERATOR OVERLOADS
//==============================================================================
Vector& Vector::operator+=(const Vector& other){
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}
Vector Vector::operator+(const Vector& other){
	Vector pp;
	pp.x = this->x + other.x;
	pp.y = this->y + other.y;
	pp.z = this->z + other.z;
	return pp;
}
Vector& Vector::operator-=(const Vector& other){
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}
Vector Vector::operator-(const Vector& other){
	Vector pp;
	pp.x = this->x - other.x;
	pp.y = this->y - other.y;
	pp.z = this->z - other.z;
	return pp;
}
Vector& Vector::operator*=(const double scale){
	this->x *= scale;
	this->y *= scale;
	this->z *= scale;
	return *this;
}
Vector Vector::operator*(const double scale){
	Vector pp;
	pp.x = this->x * scale;
	pp.y = this->y * scale;
	pp.z = this->z * scale;
	return pp;
}
Vector& Vector::operator/=(const double scale){
	this->x /= scale;
	this->y /= scale;
	this->z /= scale;
	return *this;
}
Vector Vector::operator/(const double scale){
	Vector pp;
	pp.x = this->x / scale;
	pp.y = this->y / scale;
	pp.z = this->z / scale;
	return pp;
}
bool Vector::operator==(const Vector& other){
	return
		this->x == other.x &&
		this->y == other.y &&
		this->z == other.z;
}
bool Vector::operator!=(const Vector& other){
	return !(this->operator==(other));
}
double& Vector::operator[](const int index){
	return this->data[index];
}


//==============================================================================
// LINE SEGMENT CLASS
//==============================================================================
// Handles keeping the defining points of a line segment and also can check for
// an intersection
//==============================================================================
LineSeg::LineSeg(){
}
LineSeg::LineSeg(const Point& p1, const Point& p2){
	this->p1=p1;
	this->p2=p2;
}
LineSeg::LineSeg(Point p1, const Vector& v){
	this->p1=p1;
	this->p2=p1+v;
}
Point& LineSeg::operator[](const int& index){
	if(index==1) return this->p2;
	return this->p1; // default for any num not 1
}
bool LineSeg::intersect(LineSeg& l2){
	double ua;
	double ub;
	LineSeg &l1=*this;

	double a_top[2][2];
	double b_top[2][2];
	double denom[2][2];

	a_top[0][0] =       l2[0][0] - l1[0][0];
	a_top[0][1] = -1* ( l2[1][0] - l2[0][0] ) ;
	a_top[1][0] =       l2[0][1] - l1[0][1];
	a_top[1][1] = -1* ( l2[1][1] - l2[0][1] );

	b_top[0][0] = l1[1][0] - l1[0][0];
	b_top[0][1] = l2[0][0] - l1[0][0];
	b_top[1][0] = l1[1][1] - l1[0][1];
	b_top[1][1] = l2[0][1] - l1[0][1];

	denom[0][0] =       l1[1][0] - l1[0][0];
	denom[0][1] = -1* ( l2[1][0] - l2[0][0] );
	denom[1][0] =       l1[1][1] - l1[0][1];
	denom[1][1] = -1* ( l2[1][1] - l2[0][1] );

	double bot_det = (denom[0][0]*denom[1][1]) - (denom[0][1]*denom[1][0]);
	double a_top_det = (a_top[0][0]*a_top[1][1]) - (a_top[0][1]*a_top[1][0]);
	double b_top_det = (b_top[0][0]*b_top[1][1]) - (b_top[0][1]*b_top[1][0]);

	if(bot_det==0) return false; // the lines are parralel

	ua=a_top_det/bot_det;
	ub=b_top_det/bot_det;

	//these are just roughly guessed numbers
	//i was having trouble with floating points math
	//the ends of lines were rarely returning as colliding
	if(ua>0.000000000000005 && ua<0.999999999999995 && ub>0.000000000000005 && ub<0.999999999999995)
		return true;

	return false;
}
Point LineSeg::intersection(LineSeg& l2){
	double ua;
	double ub;
	LineSeg &l1=*this;

	double a_top[2][2];
	double b_top[2][2];
	double denom[2][2];

	a_top[0][0] =       l2[0][0] - l1[0][0];
	a_top[0][1] = -1* ( l2[1][0] - l2[0][0] ) ;
	a_top[1][0] =       l2[0][1] - l1[0][1];
	a_top[1][1] = -1* ( l2[1][1] - l2[0][1] );

	b_top[0][0] = l1[1][0] - l1[0][0];
	b_top[0][1] = l2[0][0] - l1[0][0];
	b_top[1][0] = l1[1][1] - l1[0][1];
	b_top[1][1] = l2[0][1] - l1[0][1];

	denom[0][0] =       l1[1][0] - l1[0][0];
	denom[0][1] = -1* ( l2[1][0] - l2[0][0] );
	denom[1][0] =       l1[1][1] - l1[0][1];
	denom[1][1] = -1* ( l2[1][1] - l2[0][1] );

	double bot_det = (denom[0][0]*denom[1][1]) - (denom[0][1]*denom[1][0]);
	double a_top_det = (a_top[0][0]*a_top[1][1]) - (a_top[0][1]*a_top[1][0]);
	double b_top_det = (b_top[0][0]*b_top[1][1]) - (b_top[0][1]*b_top[1][0]);

	if(bot_det==0) return l1.p1; // the lines are parralel - so this seems the most sensible out of a non-sense situation
	//the above happens in 2 cases, the lines are concurent or they never intersect

	ua=a_top_det/bot_det;
	ub=b_top_det/bot_det;

	double x = (l2[1][0] - l2[0][0]) * ub ; //the amount down this line segment that the intersection occured
	x += l2[0][0] ; // the offset

	double y = (l1[1][1] - l1[0][1]) * ua ; //the amount down this line segment that the intersection occured
	y += l1[0][1] ; // the offset

	return Point(x,y,0);
}
Vector LineSeg::direction(){
	return Vector(p1,p2);
}
