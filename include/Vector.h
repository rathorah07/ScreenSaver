#ifndef KG_VECTOR_H
#define KG_VECTOR_H

/**
* Vector class
* This class os responsible for computing if a collision happens between two balls.
* It is class that defines vectors and allows us the use basic vector operations
* such as addition, subtraction, scalar multiplication, scalar product between two vectors
* and calculating unit vectors in given direction.
*/
class Vector{
	public :
	/** Variable members of the class
	*/
	float* _vector; /**<array of co-ordinates in different dimensions */
	int length; /**<number of dimensions of the vector */

	public :
	/**
	* Member functions of the class
	*/

	/**
	* Constructor of the class
	* It initializes a new vector of dimension 2
	*/
	Vector();

	/**
	* Another constructor of the class
	* @param x : co-ordinate of the vector in the X dimension
	* @param y : co-ordinate of the vector in the Y dimension
	* It initializes a new vector of dimension 2 with the given co-ordinates in the X and Y dimension
	*/
	Vector(float x, float y);

	/**
	* Addition
	* @param vector2 : vector to be added to the vector corresponding to the given vector object
	* defines commponent wise addition of given 2 vectors
	*/
	Vector addition(Vector& vector2);

	/**
	* Multiplication with a scalar
	* @param scalar : scalar to be multiplied to the vector corresponging to the given vector object
	* defines multiplication of a scalar with a given vector
	*/
	Vector scalar_multiplication(float scalar);

	/**
	* Subtraction
	* @param vector2 : determines the vector which is to be subtracted from the vector corresponding to the
	* given vector object
	* defines component wise subctraction of given two vectors
	*/
	Vector subtraction(Vector& vector2);

	/**
	* Scalar product of two vectors
	* @param vector2 : determines the vector whose scalar product is ti be calculated with the vector
	* corresponding to the given vector object
	* defines dot product between two given vectors
	* @return the result of the scalar product
	*/
	float scalar_product(Vector& vector2);

	/**
	* Unit vector
	* determines the unit vector in the direction of the given vector object
	* @return the unit vector in the reqiured direction
	*/
	Vector unit_vector();
};
#endif
