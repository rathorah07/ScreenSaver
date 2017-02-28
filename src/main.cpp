#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <time.h>
#include <queue>
#include <vector>
#include <stdio.h>
#include <vector>
#include <sstream>
#include "Vector.h"
#include "Circle.h"
#include "Collision.h"
#include "Variable.h"
#include "Display.h"
#include "Collision.h"
#include "Key_Mouse_Func.h"
#include "Menu.h"
using namespace std;





int main(int argc,char **argv){
	#ifdef DEBUG
	cout<<"IN DEBUG MODE\n";
	#endif
	srand( time(NULL) );
	if(argc == 2)
	if(sscanf(argv[1],"%i",&num_balls)!=1){
		#ifdef DEBUG
		cout << "Number of threads not integer";
		cout << "The number of balls are " << num_balls << endl;
		#endif
	}

	INITIALIZE_GLOBAL_MEMORY();

	for(int i = 0; i < circle.size(); i++)
	Initcircle(circle[i]);
	#ifdef DEBUG
	cout << " Circles created succesfully\n ";
	#endif

	glutInit(&argc, argv); // Initialize glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition (0,0);
	glutInitWindowSize (Width, Height); // Set the width and height of the window
	glutCreateWindow ("Screen Saver"); // Set the title for the window
	#ifdef DEBUG
	cout << " Window created succesfully\n ";
	#endif

	init();
	glutDisplayFunc(display);
	#ifndef DEBUG
	glutFullScreen();
	#endif

	#ifdef DEBUG
	cout << " Entered to Full Screen\n ";
	#endif

	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_key);
	glutMouseFunc(mouse);
	glutCreateMenu(menu);

	// Add menu items
	glutAddMenuEntry("Pause / Play", MENU_FRONT);
	glutAddMenuEntry("Change Color", MENU_SPOT);
	glutAddMenuEntry("Add a BALL", MENU_BACK_RIGHT);
	glutAddMenuEntry("Remove BALL", MENU_BACK_LEFT);

	// Associate a mouse button with menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);    // Extra features by right clicking

	glutMainLoop();

	return 0;

}

	/** Maintain balls by threads
  	 *
  	 * @param arg a void* pointer
  	 * Input is a  pointer to the index of ball in the vector array.
  	 * Check collison for given ball and move and update its velocity.
	 */

void* thread_func(void* arg){

	int* in = (int*) arg;
	int val = *in;

	queue<int> metemp;             		// temporary message queue

	pthread_mutex_lock(&lock);			// lock mutex to check collison


	int can;
	while(!mein.empty())				// check collision and update velocity if so
	{
		can = mein.front();
		mein.pop();
		collision(circle[val] , circle[can]);
		metemp.push(can);
	}

	while(!metemp.empty())	           // pushing the new message received into message input queue
	{
		can = metemp.front();
		metemp.pop();
		mein.push(can);
	}

	pthread_mutex_unlock(&lock);

	pthread_mutex_lock(&lock);                // locking mutex so other thread cann't update positon while this thread is updating

	circle[val].move_circle(Width, Height);	  // moving the circle
	mein.push(val);
	pthread_mutex_unlock(&lock);			  // Unlocking Mutex to allow other thread to update information

	return NULL;
}

	/** Initialise a newly created circle in free space
	*
	* @param Refernce to a Circle
	* Input Circle is given a randomize velocity , mass , location to free space , mass ,Color.
	*/

void Initcircle(Circle &in_circle)
{

	int velsetx = rand() % 2;					//! variables to give positive or negative velocity
	int velsety = rand() % 2;

 	velsetx = (velsetx == 1) ? 1 : -1;
	velsety = (velsety == 1) ? 1 : -1;

	in_circle.para = 0.4;
	float para = in_circle.para;

	in_circle.vel[0] =  para*velsetx*(rand() % (11));           //! randomize velocity from (0,11*para)
	in_circle.vel[1] =  para*velsety*(rand() % (11));

	in_circle.color[0] = 0.1*(rand()%10);
	in_circle.color[1] = 0.1*(rand()%10);						//! randomize color components from (0,0.9)
	in_circle.color[2] = 0.1*(rand()%10);

	bool flag ;				                                 // ensuring that created ball is not overlaping on other ball or wall
	do{
		flag = true;
		in_circle.radius = 5*(rand() % 7+4);				// random radius between (20,50)

		in_circle.pos[0] = in_circle.radius + (rand()%(Width - 2*(int)(in_circle.radius + 1)));    //Wall Overlap along-x handled here

		in_circle.pos[1] = in_circle.radius + (rand()%((Height - 100)-2*(int)(in_circle.radius + 1))) + 50; // Wall Overlap along-y handled here

	for(int i = 0; i < counter; i++)  					// overlap with balls handled here
	{
		float centre_distance = (((circle[i].pos[0] - in_circle.pos[0])*(circle[i].pos[0] - in_circle.pos[0])) + ((circle[i].pos[1] - in_circle.pos[1])*(circle[i].pos[1] - in_circle.pos[1])));
		if(centre_distance -0.5 <= (circle[i].radius + in_circle.radius)*(circle[i].radius + in_circle.radius))
		{
			flag = false;
			break;
		}
	}


}while(!flag);

	counter++;				//increased the number of initialised ball

	in_circle.mass   = in_circle.radius*36 + 1;     // mass given proportion to radius

}
