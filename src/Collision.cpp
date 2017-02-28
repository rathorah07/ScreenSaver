#include "Collision.h"
#include "Circle.h"
#include "Vector.h"
#include "Variable.h"
#include <iostream>
using namespace std;
/**
* Collision Detection
* @param circle1 : one of the circles on which collision detection is done
* @param cirlce2 : another circle on which collision detection is done
* determines whether collsion occurs between given 2 circles and if so,
* changes their velocoties accordingly
*/
void collision(Circle& circle1, Circle& circle2){

	Vector normal(circle2.pos[0] - circle1.pos[0], circle2.pos[1] - circle1.pos[1]);/**<vector joining the centres of the given 2 circles */

	float mass1 = circle1.mass;
	float mass2 = circle2.mass;

	Vector unit_normal = normal.unit_vector(); /**<unit vector along the normal of the collison*/
	Vector unit_tangent(-1.0 * (unit_normal._vector[1]), unit_normal._vector[0]); /**<unit vector along the tangent at the point of collison */

	// velocity vectors of the balls
	Vector v1(circle1.vel[0], circle1.vel[1]); /**<velocity vector of circle1 */
	Vector v2(circle2.vel[0], circle2.vel[1]); /**<velocity vector of cirlce2 */

	// dividing the velocity vectors into the rectangular normal and the tangential directions
	float v1t = v1.scalar_product(unit_tangent); /**<tangential component of velocity of circle1 */
	float v1n = v1.scalar_product(unit_normal); /**<normal component of velocity of cirlce1 */
	float v2t = v2.scalar_product(unit_tangent); /**<tangential component of velocity of circle2 */
	float v2n = v2.scalar_product(unit_normal); /**<normal component of velocity of circle2 */

	float approach = v2n - v1n; /**<velocity of approach of the two circles */
	/**
	* condition to check whether a collision occurs between the circles
	*/
	if (normal.scalar_product(normal) <= ((circle1.radius + circle2.radius) * (circle1.radius + circle2.radius))){
		/**
		* velocity of approach must be less than 0 for the collision to happen
		*/
		if (approach > 0){
			return ;
		}

	/**
	* calculating new normal velocities after collision
	*/
	float v1n_ = (v1n * (mass1 - mass2) + 2 * mass2 * v2n) / (mass1 + mass2);
	float v2n_ = (v2n * (mass2 - mass1) + 2 * mass1 * v1n) / (mass1 + mass2);

	/**
	* calculating the final velocity vectors
	*/
	Vector temp = unit_normal.scalar_multiplication(v1n_);
	Vector v1f = (unit_tangent.scalar_multiplication(v1t)).addition(temp);

	temp = unit_normal.scalar_multiplication(v2n_);
	Vector v2f = (unit_tangent.scalar_multiplication(v2t)).addition(temp);

	/**
	* updating the velocities of the circles
	*/
	circle1.vel[0] = v1f._vector[0];
	circle1.vel[1] = v1f._vector[1];
	circle2.vel[0] = v2f._vector[0];
	circle2.vel[1] = v2f._vector[1];

	#ifdef DEBUG
	cout << circle1.vel[0] << " " << circle1.vel[1] << " " << circle2.vel[0] << " " << circle2.vel[1] << endl;
	#endif
	}
}
