#include <queue>
#include <pthread.h>
#include "Circle.h"
#include "Variable.h"
using namespace std;

int  num_balls = 5;; /**<number of balls on the screen as input by the user */
queue<int> mein, meout; /**<queues for effective sychronization among the threads */
bool paused = false; /**<boolean required to determine the state of the Screen saver */
bool ball_selected = false; /**<boolean reqiured to whether a ball is currently selected on the screen */
int ball_speed_index = -1 ; /**<determines which ball's speed is being controlled. Default is -1 */
std :: vector<pthread_t> thread; /**<global vector of the threads controlling individual balls */
std :: vector<Circle> circle; /**<global vector containg the objects of each ball currently on the screen */

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; /**<Mutex Lock 1 */
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER; /**<Mutex Lock 2 */
MENU_TYPE show = MENU_BACK_RIGHT;
#ifdef DEBUG
	int Width = 600.0; /**<Width of the display screen */
	int Height = 600.0; /**<Height of the display screen */
#endif

#ifndef DEBUG
	int Width = 1366.0; /**<Width of the display screen */
	int Height = 768.0; /**<Height of the display screen */
#endif
int counter = 0; /**<global counter required in initializing the complete system */
float mouse_x; /**<x co-ordinate of the mouse pointer on the screen */
float mouse_y; /**<y co-ordinate of the mouse pointer on the screen */


/**
* Initialize function
* It intializes all the global variables that were not intialized earliar
*/
void INITIALIZE_GLOBAL_MEMORY()
{
	thread.resize(num_balls);
	circle.resize(num_balls);
}
