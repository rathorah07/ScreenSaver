#ifndef VARIABLES_H
#define VARIABLES_H
#include <queue>
#include <pthread.h>
#include "Circle.h"
using namespace std;

#define PI 3.1415926535898
extern int  num_balls; /**<number of balls on the screen as input by the user */
extern queue<int> mein, meout; /**<queues for effective sychronization among the threads */
extern bool paused; /**<boolean required to determine the state of the Screen saver */
extern bool ball_selected; /**<boolean reqiured to whether a ball is currently selected on the screen */
extern int ball_speed_index; /**<determines which ball's speed is being controlled. Default is -1 */
extern std :: vector<pthread_t> thread; /**<global vector of the threads controlling individual balls */
extern std :: vector<Circle> circle; /**<global vector containg the objects of each ball currently on the screen */

extern pthread_mutex_t lock; /**<Mutex Lock 1 */
extern pthread_mutex_t lock2; /**<Mutex Lock 2 */
extern int Width; /**<Width of the display screen */
extern int Height; /**<Height of the display screen */
extern int counter; /**<global counter required in initializing the complete system */
extern float mouse_x; /**<x co-ordinate of the mouse pointer on the screen */
extern float mouse_y; /**<y co-ordinate of the mouse pointer on the screen */
/**
* An Enumneration of the Menu
*/
enum MENU_TYPE
{
        MENU_FRONT,
        MENU_SPOT,
        MENU_BACK_RIGHT,
        MENU_BACK_LEFT,
};

//! Assign a default value
extern MENU_TYPE show;

/**
* prototypes of vatious function described later
*/
void Initcircle(Circle &in_circle);
void* thread_func(void* arg);
void INITIALIZE_GLOBAL_MEMORY();


#endif
