#include <math.h>
#include "Vector.h"
#include <iostream>
using namespace std;

Vector :: Vector(){
	length = 2;
	_vector = new float[length];
	_vector[0] = 0;
	_vector[1] = 0;
}

Vector :: Vector(float x, float y){
	length = 2;
	_vector = new float[length];
	_vector[0] = x;
	_vector[1] = y;
}

Vector Vector :: addition(Vector& vector2){
	return Vector(_vector[0] + vector2._vector[0], _vector[1] + vector2._vector[1]);
}

Vector Vector :: subtraction(Vector& vector2){
	return Vector(_vector[0] - vector2._vector[0], _vector[1] - vector2._vector[1]);
}

Vector Vector :: scalar_multiplication(float scalar){
	return Vector(scalar * _vector[0], scalar * _vector[1]);
}

float Vector :: scalar_product(Vector& vector2){
	float output = _vector[0]*(vector2._vector[0]) + _vector[1]*(vector2._vector[1]);
	return output;
}

Vector Vector :: unit_vector(){

	float norm = sqrt(_vector[0]*_vector[0] + _vector[1]*_vector[1]);
	return Vector(_vector[0] / norm, _vector[1] / norm);
}
