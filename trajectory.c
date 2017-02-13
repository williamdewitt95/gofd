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

double rotation, tank_x, tank_y, tank_z;

typedef struct shell_params {
     double x_local;
     double y_local;
// The next four are immutable and set at the time the shell is fired
     double rotation;
     double tank_x;
     double tank_y;
     double tank_z;
// The next three will be the computed global coordinates of the shell
     double x_global;
     double y_global;
     double z_global;
} shell_type;

shell_type shell;
   
void init(){

    V     = 500.0;   // Initial Velocity            (m/sec)
    m     = 50.00;   // Projectile Mass             (kg)
    angle = 75.0;    // Angle of Gun above azimuth  (degrees)
    G     = 9.81;    // Acceleration due to Graviey (m/sec^2)
    C     = 0.05;  // Drag Coefficient 

    h     = 0.00001;   // Stepsize for RK4 method

    // Set initial tank position and gun rotation (degrees)

    tank_x = 0;
    tank_y = 0;
    tank_z = 0;
    rotation = 0.0;

    // Set the initial value of x, y, and t

    t = 0.0;
    y = 0.0;
    x = 0.0;

    // Initial values of velocity compoents

    p = V*cos(angle*M_PI/180.0);
    q = V*sin(angle*M_PI/180.0);

    // Put the initial values in the struct

    shell.rotation=rotation;
    shell.tank_x=tank_x;
    shell.tank_y=tank_y;
    shell.tank_z=tank_z;


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

void vmatm (int SIZE, double *pA, double *pB)

// Matrix-vector multiplication
// pA is a pointer to the first element of matrix A
// pB is a pointer to the first element of vector B
// On return, B will contain transformed coordinates
{
   int i, j;
   double temp[4];

   for (i=0; i<SIZE; i++)
             temp[i] = 0.0;

   for (i=0; i < SIZE; i++)
     for (j = 0; j < SIZE; j++)
           temp[i] += *(pA+(i*SIZE+j)) * *(pB+j);
   
   for (i=0; i<SIZE; i++)
         *(pB+i) = temp[i];

}


void buildTranslate( double x, double y, double z, double *pA )
// Constructs tranlation matrix to translate along x, y, and z axes
{
     pA[ 0] = 1.0; pA[ 1] = 0.0; pA[ 2] = 0.0; pA[ 3] =   x;
     pA[ 4] = 0.0; pA[ 5] = 1.0; pA[ 6] = 0.0; pA[ 7] =   y;
     pA[ 8] = 0.0; pA[ 9] = 0.0; pA[10] = 1.0; pA[11] =   z;
     pA[12] = 0.0; pA[13] = 0.0; pA[14] = 0.0; pA[15] = 1.0;
}

void buildRotateZ( double theta, double *pA )
{
// Constructs rotation matrix about Z axis

     double phi;

     // Convert degrees to radians

     phi = theta * M_PI / 180.0;

     pA[ 0] =  cos(phi); pA[ 1] = sin(phi); pA[ 2] = 0.0; pA[ 3] = 0.0;
     pA[ 4] = -sin(phi); pA[ 5] = cos(phi); pA[ 6] = 0.0; pA[ 7] = 0.0;
     pA[ 8] = 0.0;       pA[ 9] = 0.0;      pA[10] = 1.0; pA[11] = 0.0;
     pA[12] = 0.0;       pA[13] = 0.0;      pA[14] = 0.0; pA[15] = 1.0;
}      




void applyTransformation( double *vp, int vpts, double *TM ) 
// Applies the given transformation matrix TM to the vector vp containing
// all of the homegenous coordinates to define the object
{
	double temp[4];
	double *tmp;
    int i;

	tmp = &temp[0];

	for (i=0;i<vpts;i++)
	{
		*(tmp+0)= *(vp+(i*4)+0);
		*(tmp+1)= *(vp+(i*4)+1);
		*(tmp+2)= *(vp+(i*4)+2);
		*(tmp+3)= *(vp+(i*4)+3);
		vmatm( 4, TM, tmp );
		*(vp+(i*4)+0) = *(tmp+0); 
		*(vp+(i*4)+1) = *(tmp+1); 
		*(vp+(i*4)+2) = *(tmp+2); 
		*(vp+(i*4)+3) = *(tmp+3); 
    }

}

void fromTankCoordsToGlobalCoords( shell_type shell ) {
    
     double tmpstore[4];
     double TM[16], *pTM;
 
     pTM = &TM[0];

     // Pull variable from shell structure into tmp vector for transformation    
     tmpstore[0] = shell.x_local;
     tmpstore[1] = 0.0;
     tmpstore[2] = shell.y_local;
     tmpstore[3] = 1.0;

     // Build the appropriate rotation matrix
     buildRotateZ( shell.rotation, pTM );
     // Apply the rotation
     applyTransformation( tmpstore, 1, pTM );
     // Build the appropriate translation matrix
     buildTranslate( shell.tank_x, shell.tank_y, shell.tank_z, pTM);
     // Apply the tanslation
     applyTransformation( tmpstore, 1, pTM );

     // Copy results back to the structure
     shell.x_global = tmpstore[0]; 
     shell.y_global = tmpstore[1]; 
     shell.z_global = tmpstore[2]; 
     
}

 
     
int main() {
    double xtemp, ytemp;
    init();
    while(y >= 0.0) {
        //cout << t << " " << x << "  " << y << endl;
        
        // Update the struct with the new local x and y //
        shell.x_local = x;
        shell.y_local = y;


        // Using tank coords and rotation stored in struct, 
        // rotate the local coordinates and then translate them
        // to the position of the tank using matrix methods learned
        // in CSC 315.
        fromTankCoordsToGlobalCoords( shell_type &shell ); 
        
        printf(" %f %f %f\n", t, x, y);
        step();
    }
}
