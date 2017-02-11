#include <stdio.h>
#include <math.h>

// Projectile Calculations Using Runge-Kutta Method
//   Includes frictional drag and gravity, but no crosswind calculation
//   
//   Andrew J. Pounds, Ph.D.
//   Department of Computer Science
//   Mercer University
//   Spring 2006
//   
//   Modified Spring 2016 to include damping based
//   on military documents and converted to SI units.  

// Program Constants 

double V, m, angle, G, C, h;
double t, y, x;
double p, q;

void init(){
 
V     = 500.0;   // Initial Velocity            (m/sec)
m     = 50.00;   // Projectile Mass             (kg)
angle = 75.0;    // Angle of Gun above azimuth  (degrees)
G     = 9.81;    // Acceleration due to Graviey (m/sec^2)
C     = 0.05;  // Drag Coefficient 

h     = 0.00001;   // Stepsize for RK4 method

// Set the initial value of x, y, and t

t = 0.0;
y = 0.0;
x = 0.0;

// Initial values of velocity compoents

p = V*cos(angle*M_PI/180.0);
q = V*sin(angle*M_PI/180.0);

}


// Compute the drag based on the 155 mm HE Shell
double drag( double speed ){
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
double f ( double p, double q, double C ){
    double speed;
    speed = sqrt(p*p+q*q);
	return -drag(speed)*p*speed/m;
    }

// Function for motion in vertical direction
double  g ( double p, double q, double C, double G){
    double speed;
    speed = sqrt(p*p+q*q);
    return -drag(speed)*q*speed/m-G;
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
    init();
    while(y >= 0.0) {
        //cout << t << " " << x << "  " << y << endl;
        printf(" %f %f %f\n", t, x, y);
        step();
    }
}
