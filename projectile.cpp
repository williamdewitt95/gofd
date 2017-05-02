#include "projectile.h"
#include <iostream>
using std::cout;

Projectile::Projectile(Point center){
	this->baseInit(center,center,45,0);
}

Projectile::Projectile(Point center, Point tankStart, double angleV, double angleH){
	this->baseInit(center,tankStart,angleV,angleH);
}

void Projectile::baseInit(Point center, Point tankStart, double angleV, double angleH){
	this->center = center;
	this->oldCenter = center;
	this->tankStart = tankStart;
	this->angleV = angleV;
	this->angleH = angleH;
	this->mass = 50.0;
	this->velocity = 50.0;
	this->C = 0.05;
	this->invincibility = 5;

	this->t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
	this->local = Point(0.0, 0.0, 0.0);

	this->p = this->velocity*cos(angleV*M_PI/180.0);
	this->q = this->velocity*sin(angleV*M_PI/180.0);
	this->h = 0.01;

	this->trailInterval = 0;

	this->state=MOVING;

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

void Projectile::draw(){
	if(this->state==MOVING){
		GLUquadricObj *shellCasing, *shellPoint, *shellBottom;

		glPushMatrix();
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

		//clean up
		gluDeleteQuadric(shellCasing);
		gluDeleteQuadric(shellPoint);
		gluDeleteQuadric(shellBottom);

		drawTrails(trails);
	}
	else if (this->state==EXPLODING) {
		for(int i=0; i<explosions.size();i++){
			drawExplosion(&explosions[i]);
		}
	}
}

void Projectile::update()
{
	if(this->state == MOVING){

		this->oldCenter.x = this->center.x;
		this->oldCenter.y = this->center.y;
		this->oldCenter.z = this->center.z;
		//sync with actual time
		double currTime = glutGet(GLUT_ELAPSED_TIME)/1000.0 ;
		this->h = (currTime - this->t) / 10.0;
   		while( (float)this->t < (float)currTime){ step(); }
   		// this->t = currTime;

		// step();
		Point temp = Point(this->local.x, 0, this->local.z);
		temp = temp.rotatePoint(this->angleH, false, false, true);
		temp = temp.translatePoint(this->tankStart.x, this->tankStart.y, this->tankStart.z);
		
		this->center.x = temp.x;
		this->center.y = temp.y;
		this->center.z = temp.z;

		if(this->invincibility>0)
			invincibility--;

		if (this->trailInterval == 20) {
			Trail t;
			t.x = center.x;
			t.y = center.y;
			t.z = center.z;
			t.decay = 70;
			t.staticDecay = t.decay;
			cout << "make trail\n";
			this->trails.push_back(t);
			this->trailInterval = 0;
		}
		this->trailInterval++;

		//check to see if it has hit the ground. If so, then we have hit and need to explode
		//if z<=0, start exploding and generate random values for each splode
		if(center.z <= 0){
			// printf("angle %f\t\tdeath coordinates: %f, %f",this->angleV,this->center.x, this->center.y);
			// printf("\t\tstart coordinates: %f, %f\n",this->tankStart.x,this->tankStart.y);
			double distance = sqrt((this->center.x-this->tankStart.x)*(this->center.x-this->tankStart.x) + 
				(this->center.y-this->tankStart.y)*(this->center.y-this->tankStart.y));
			// printf("%.3f\t %d\n",this->angleV,(int)distance);

			this->state=EXPLODING;
			this->center.z = 0.0;
			int splodes = 3 + (rand() % 3);
			for (int i=0;i < splodes;i++) {
				Explosion n;
				n.x = center.x + ((((double) rand() / (RAND_MAX)) - 0.5) * 5);
				n.y = center.y + ((((double) rand() / (RAND_MAX)) - 0.5) * 5);
				n.z = center.z + ((double) rand() / (RAND_MAX));
				n.decay = 15 + (rand() % 5);
				n.staticDecay = n.decay;
				n.expansionRate = (0.25 + ((double) rand() / (RAND_MAX))) / 5;
				n.radius = 0.05 + (((double) rand() / (RAND_MAX)) * 1.0);
				explosions.push_back(n);
			}
		}
	}
	else if (this->state==EXPLODING){
		//now lets update the parameters of every explosion until it decays away
		for(int x=explosions.size()-1; x>=0; x--){
			explosions[x].radius += explosions[x].expansionRate;
			explosions[x].decay--;
			//remove the sphere if the radius is too small
			if(explosions[x].decay<=0)
				explosions.erase(explosions.begin()+x);
		}
		if(explosions.size()==0)
			this->state=DEAD;
	}else if(this->state==DEAD){
		//well, we are dead, so what can i say...
	}
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

void Projectile::drawExplosion(struct Explosion *ex) {
	if (ex->decay > 0) {
		glPushMatrix();
		glLoadIdentity();
		glTranslated(ex->x, ex->y, ex->z);
		//gradually change color to a dark grey (0.3, 0.3, 0.3)
		double decayRatio = (double) ex->decay / ex->staticDecay;
		float colorR = 1.0;
		float colorG = 0.65;
		float colorB = 0.13;

		colorR = 0.3 + (decayRatio * (colorR - 0.3));
		colorG = 0.3 + (decayRatio * (colorG - 0.3));
		colorB = 0.3 + (decayRatio * (colorB - 0.3));

		glColor3f(colorR, colorG, colorB);
		glutSolidSphere(ex->radius, 8, 8);
		glPopMatrix();
	}
}
void Projectile::setExploding(Point p){
	if(this->state==MOVING){
		this->state=EXPLODING;
		this->center = p;
		int splodes = 3 + (rand() % 3);
		for (int i=0;i < splodes;i++) {
			Explosion n;
			n.x = center.x + ((((double) rand() / (RAND_MAX)) - 0.5) * 5);
			n.y = center.y + ((((double) rand() / (RAND_MAX)) - 0.5) * 5);
			n.z = center.z + ((double) rand() / (RAND_MAX));
			n.decay = 15 + (rand() % 5);
			n.staticDecay = n.decay;
			n.expansionRate = (0.25 + ((double) rand() / (RAND_MAX))) / 5;
			n.radius = 0.05 + (((double) rand() / (RAND_MAX)) * 1.0);
			explosions.push_back(n);
		}
	}
}

void Projectile::setExploding(){
	setExploding(this->center);
}

void Projectile::drawTrails(std::vector<Trail>& trailList) {
	Trail t;
	for(int i=0; i<trailList.size();i++){
		t = trailList.at(i);
		if (t.decay != 0) {
			glPushMatrix();
			glLoadIdentity();
			glTranslated(t.x, t.y, t.z);
			double decayRatio = (double) t.decay / t.staticDecay;
			float colorR = 1.0;
			float colorG = 0.65;
			float colorB = 0.13;

			glEnable (GL_BLEND);
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			cout << "decay = " << t.decay << "\n";

			colorR = 0.73 + (decayRatio * (colorR - 0.3));
			colorG = 0.33 + (decayRatio * (colorG - 0.3));
			colorB = 0.83 + (decayRatio * (colorB - 0.3));

			glColor4f(colorR, colorG, colorB, decayRatio);
			glutSolidSphere(1.0f, 8, 8);
			glPopMatrix();
			trailList.at(i).decay--;
			glDisable (GL_BLEND);
		}
	}
	
}