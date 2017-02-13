#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using std::cout;
//
// Matrix Constructors
//

matrix::matrix(){

	for(int i = 0; i< 16; i++){
		if(i%5 == 0){
			ele[i] = 1;
		}else{
			ele[i] = 0;
		}
	}

}

matrix::matrix(std::vector<Vector>& columns){

}

matrix::matrix(Polygon3d object){

	matSet(object);

}

matrix::matrix(double elements[]){

	for(int i = 0; i < 16; i++){
		this->ele[i] = elements[i];
	}

	for(int i = 0; i < 16; i++){
		//cout << this->ele[i];
		//cout << "\n";
	}
}

//
// Matrix Functions
//


Vector& matrix::matTransform(Vector test){
	
	Vector *out = new Vector();

	//for(int i = 0; i < 4; i++){
		//Not sure how to handle the homogenous coordinates since the polygon3d only has x,y,z coordinates
		out->x = test.x*this->ele[0*4+0]+test.y*this->ele[0*4+1]+test.z*this->ele[0*4+2]+1*this->ele[0*4+3];
		out->y = test.x*this->ele[1*4+0]+test.y*this->ele[1*4+1]+test.z*this->ele[1*4+2]+1*this->ele[1*4+3];
		out->z = test.x*this->ele[2*4+0]+test.y*this->ele[2*4+1]+test.z*this->ele[2*4+2]+1*this->ele[2*4+3];
	//}	
	cout << out->x << out->y << out->z;
	return *out;
	
}

Vector matrix::matSet(Polygon3d object){
	
	
	
}


