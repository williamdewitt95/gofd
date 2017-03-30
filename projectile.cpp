#include "projectile.h"

Projectile::Projectile(Point center){
	this->center = center;
	this->tankStart = center;
	this->angleV = 45;
	this->angleH = 0;
	this->mass = 50.0;
	this->velocity = 50.0;
	this->C = 0.05;

	this->t = 0.0;
	this->local = Point(0.0, 0.0, 0.0);

	this->p = this->velocity*cos(angleV*M_PI/180.0);
	this->q = this->velocity*sin(angleV*M_PI/180.0);
	this->h = 0.1;

	{
		boundingBox.push_back(Polygon3d());
		auto &points = boundingBox[boundingBox.size()-1].getPoints();

		points.push_back(Point(  -5, -5,  20));
		points.push_back(Point(  -5, -5,   0));
		points.push_back(Point(   5, -5,   0));
		points.push_back(Point(   5, -5,  20));
		points.push_back(Point(  -5, -5,  20));
	}
	{
		boundingBox.push_back(Polygon3d());
		auto &points = 	boundingBox[boundingBox.size()-1].getPoints();

		points.push_back(Point(   5,  5,  20));
		points.push_back(Point(   5,  5,   0));
		points.push_back(Point(  -5,  5,   0));
		points.push_back(Point(  -5,  5,  20));
		points.push_back(Point(   5,  5,  20));
	}
	{
		boundingBox.push_back(Polygon3d());
		auto &points = boundingBox[boundingBox.size()-1].getPoints();

		points.push_back(Point(   5, -5,  20));
		points.push_back(Point(   5, -5,   0));
		points.push_back(Point(   5,  5,   0));
		points.push_back(Point(   5,  5,  20));
		points.push_back(Point(   5, -5,  20));
	}
	{
		boundingBox.push_back(Polygon3d());
		auto &points = boundingBox[boundingBox.size()-1].getPoints();

		points.push_back(Point(  -5,  5,  20));
		points.push_back(Point(  -5,  5,   0));
		points.push_back(Point(  -5, -5,   0));
		points.push_back(Point(  -5, -5,  20));
		points.push_back(Point(  -5,  5,  20));
	}

	{
		boundingBox.push_back(Polygon3d());
		auto &points = boundingBox[boundingBox.size()-1].getPoints();

		points.push_back(Point(  -5,  5,  20));
		points.push_back(Point(  -5,  5,   0));
		points.push_back(Point(  -5, -5,   0));
		points.push_back(Point(  -5, -5,  20));
		points.push_back(Point(  -5,  5,  20));
	}
}

Projectile::Projectile(Point center, Point tankStart, double angleV, double angleH)
{
	this->center = center;
	this->angleV = angleV;
	this->angleH = angleH;
	this->tankStart = tankStart;
	this->mass = 50.0;
	this->velocity = 50.0;
	this->C = 0.05;

	this->t = 0.0;
	this->local = Point(0, 0, 0);

	this->p = this->velocity*cos(angleV*M_PI/180.0);
	this->q = this->velocity*sin(angleV*M_PI/180.0);
	this->h = 0.01;
}

void Projectile::draw(){
	glPushMatrix();

	GLUquadricObj *shellCasing, *shellPoint, *shellBottom;
	glColor3f(1.0, .1, .1);
	glTranslated(center.x,center.y,center.z);
	glRotated(this->angleH, 0.0, 0.0, 1.0);
	glRotated(-this->angleV, 0, 1.0, 0);
	glTranslated(-.1, 0.0, 0.0);

	glRotated(90.0, 0.0, 1.0, 0.0);
	shellCasing = gluNewQuadric();
	gluCylinder(shellCasing, .05, .05, .2, 30, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.1, .1, .1);
	glTranslated(center.x,center.y,center.z);
	glRotated(this->angleH, 0.0, 0.0, 1.0);
	glRotated(-this->angleV, 0, 1.0, 0);
	glTranslated(0, 0, 0);

	glRotated(90.0, 0.0, 1.0, 0.0);
	shellBottom = gluNewQuadric();
	gluDisk(shellBottom, 0, .05, 30, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(center.x,center.y,center.z);
	glRotated(this->angleH, 0.0, 0.0, 1.0);
	glRotated(-this->angleV, 0, 1.0, 0);
	glTranslated(.1, 0.0, 0.0);
	glRotated(90.0, 0.0, 1.0, 0.0);

	shellPoint = gluNewQuadric();
	gluCylinder(shellPoint, .05, .00, .4, 30, 4);
	glPopMatrix();
}

void Projectile::update()
{
	if(center.z > 0)
	{
		step();
		Point temp = Point(this->local.x, 0, this->local.z);
		temp = temp.rotatePoint(this->angleH, false, false, true);
		temp = temp.translatePoint(this->tankStart.x, this->tankStart.y, this->tankStart.z);
		this->center.x = temp.x;
		this->center.y = temp.y;
		this->center.z = temp.z;
	}
}

std::vector<Polygon3d> Projectile::getBoundingBox(){
	return this->boundingBox;
}

// Compute the drag based on the 155 mm HE Shell
double Projectile::drag( double speed ){
    double mach, mach2, mach3, Kd;
    mach = speed / 340.29;   // Speed of sound in m/s
    mach2 = mach*mach;
    mach3 = mach*mach*mach; 
    if ( mach <= 0.90 ) { 
        Kd = 0.0579080038;
    }
    else if ( mach <= 0.96 ) {
        Kd = 44.26302428-138.8317032*mach+
            144.7922431*mach2-50.12112525*mach3;
    }
    else if ( mach <= 1.02 ) {
        Kd = 414.3525910-1262.4596066*mach+
            1280.9650680*mach2-432.7252631*mach3;
    }
    else if ( mach <= 1.22 ) {
        Kd = -0.4212674799+1.029831902*mach-0.4621525076*mach2;
    }
    else if ( mach <= 1.3 ) {
        Kd = 8.911875950-20.35167306*mach+15.77773047*mach2-
            4.085776562*mach3;
    }
    else if ( mach <= 2.6 ) {
        Kd = (0.9415+0.1327*mach);
        Kd = (Kd*Kd-1.0)/mach2;
    }
    else {
        Kd = 0.05;
    }
    return Kd;
}


// Function for motion in horizontal direction
double Projectile::f ( double p, double q, double C ){
    double speed;
    speed = sqrt(p*p+q*q);
    return -drag(speed)*p*speed/this->mass;
}

// Function for motion in vertical direction
double  Projectile::g ( double p, double q, double C){
    double speed;
    speed = sqrt(p*p+q*q);
    return -drag(speed)*q*speed/this->mass-GRAVITY;
}


void Projectile::step() {

    double f1, f2, f3, f4;
    double g1, g2, g3, g4;
    double dp, dq;

    // Begin Runge-Kutta Method Here for Systems
    f1 = f(this->p,this->q,this->C);
    g1 = g(this->p,this->q,this->C);
    f2 = f(this->p+this->h*f1/2,this->q+this->h*g1/2,this->C);
    g2 = g(this->p+this->h*f1/2,this->q+this->h*g1/2,this->C); 
    f3 = f(this->p+this->h*f2/2,this->q+this->h*g2/2,this->C);
    g3 = g(this->p+this->h*f2/2,this->q+this->h*g2/2,this->C); 
    f4 = f(this->p+this->h*f3,this->q+this->h*g3,this->C); 
    g4 = g(this->p+this->h*f3,this->q+this->h*g3,this->C); 
    dp = (f1 + 2*f2 + 2*f3 + f4 ) / 6.0;
    dq = (g1 + 2*g2 + 2*g3 + g4 ) / 6.0;
    this->local.x = this->local.x + this->p*this->h + 0.5*dp*this->h*this->h; 
    this->local.z = this->local.z + this->q*this->h + 0.5*dq*this->h*this->h; 
    this->p = this->p + dp*this->h;
    this->q = this->q + dq*this->h;
    this->t = this->t + this->h;
}
