#ifndef CIRCLE_H
#define CIRCLE_H
#define PI 3.1415926535898
/**
* Circle class
* This class brings out most of the features of the program.
* It is responsible for creating the balls, moving them, speeding them up and down and most importantly
* assigning them random co-ordinates of the centre, velocities and radius at the begining of the program.
*/
class Circle{

	public:
		/**
		* Variable members of the class
		*/
		float pos[2]; /**<determines the co-ordinates of the centre of the circle */
		float vel[2]; /**<determines the components of the velocities of the circle in the X and the Y directions */
		float radius; /**<determines the radius of the circle */
		float color[3]; /**<determines the color that is assigned to the circle */
		float mass; /**<determines mass of the circle that is propotional to the radius of the circle */
		float para;/**<a speed parameter */
		/**
		* Member functions of the class
		*/

		/**
		* Constructor of the class
		* This constructor assigns random co-ordinates of the centre, velocities, radius, mass(propotional to the radius) to the circle
		* constrained under certain boundary conditions as described later
		*/
		Circle();

		/**
		* Speed Up function
		* It increases the speed of the circle as and when the user calls for it.
		* This function increases the speed of the circle in both the X and Y directions uniformly under predefined maximums
		* @see vel
		*/
		void speed_up();

		/**
		* Speed Down function
		* It decreases the speed of the circle as and when the user call for it.
		* This function decreases the speed of the circle in both the X and Y directions uniformly under predefined minimums
		* @see vel
		*/
		void speed_down();

		/**
		* Create circle function
		* It create a circle on the screen display in accordance to the current values of the co-ordinates of the centre
		* of the circle
		*/
		void create_circle();

		/** Move circle function
		* It is responsible for checking if the circle undergoes collision with the walls of the display screen
		* @param Width : width of the display screen
		* @param Height : height of the display screen
		*/
		void move_circle(int Width, int Height);
};
#endif
