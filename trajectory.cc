#include <iostream>
#include <stdlib.h>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;

//
// Projectile Calculations Using Runge-Kutta Method
//   Includes frictional drag and gravity, but no crosswind calculation
//   
//   Andrew J. Pounds, Ph.D.
//   Department of Computer Science
//   Mercer University
//   Spring 2006
//

// Program Constants 

double V     = 500.0;   // Initial Velocity            (ft/sec)
double angle = 75.0;    // Angle of Gun above azimuth  (degrees)
double G     = 32.0;    // Acceleration due to Graviey (ft/sec^2)
double C     = 0.0025;  // Coefficient of friction due to air

double h     = 0.00001;   // Stepsize for RK4 method

// Set the initial value of x, y, and t

double t = 0.0;
double y = 0.0;
double x = 0.0;

// Initial values of velocity compoents

double p = V*cos(angle*M_PI/180.0);
double q = V*sin(angle*M_PI/180.0);



// Function for motion in horizontal direction
double f ( double p, double q, double C ){
	return -C*p*sqrt(pow(p,2)+pow(q,2));
    }

// Function for motion in vertical direction
double  g ( double p, double q, double C, double G){
    return -C*q*sqrt(pow(p,2)+pow(q,2))-G;
    }


void step() {

double f1, f2, f3, f4;
double g1, g2, g3, g4;
double dp, dq;

    // Begin Runge-Kutta Method Here for Systems
	f1 = f(p,q,C);
	g1 = g(p,q,C,G);
	f2 = f(p+h*f1/2,q+h*g1/2,C);
	g2 = g(p+h*f1/2,q+h*g1/2,C,G); 
	f3 = f(p+h*f2/2,q+h*g2/2,C);
	g3 = g(p+h*f2/2,q+h*g2/2,C,G); 
	f4 = f(p+h*f3,q+h*g3,C); 
	g4 = g(p+h*f3,q+h*g3,C,G); 
	dp = (f1 + 2*f2 + 2*f3 + f4 ) / 6.0;
	dq = (g1 + 2*g2 + 2*g3 + g4 ) / 6.0;
	x = x + p*h + 0.5*dp*h*h; 
	y = y + q*h + 0.5*dq*h*h; 
	p = p + dp*h;
	q = q + dq*h;
	t = t + h;
}

int main() {
    while(y >= 0.0) {
	cout << t << " " << x << "  " << y << endl;
    step();
    }
    exit(0);
    }
