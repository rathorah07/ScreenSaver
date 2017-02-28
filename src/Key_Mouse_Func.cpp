#include "Key_Mouse_Func.h"
#include "Circle.h"
#include "Variable.h"
#include <iostream>
#include <cstdlib>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
using namespace std;

/**
* Check Selecetion function
* @param x : x co-ordinate of the mouse current location
* @parma y : y co-ordinate of the mouse current location
* @param i : circle index to check
* It checks whether the current mouse pointer co-ordinates lies over circle with index "i"
* @return boolean result of the function
*/
bool check_selection(float x , float y, int i)
{
	float dis = (circle[i].pos[0] - x)*(circle[i].pos[0] - x) + (circle[i].pos[1] - y)*(circle[i].pos[1] - y);
	if (dis <= (circle[i].radius)*(circle[i].radius))
		return true;
	else
		return false;
}

/**
* Keyboard input function
* @param key : input from the keyboard
* @param x : state command from openGL
* @param y : state command from openGL
* co-ordinates the user inputs throught the keyboard
*/
void keyboard(unsigned char key, int x, int y)
{
	if (key == ' ')
    {
    	#ifdef DEBUG
    	cout << "System called for pause / play" << endl;
    	#endif

    	paused = (paused == true)? 0 : 1;
		ball_speed_index = -1;
	}

	if (key == 27){
		#ifdef DEBUG
		cout << "System called for exit!" << endl;
		#endif

		exit(0);
	}
}

/**
* Keyboard input function
* @param key : input from the keyboard
* @param x : state command from openGL
* @param y : state command from openGL
* co-ordinates the user inputs throught the keyboard for speed control
*/
void special_key(int key,int x,int y)
{
	if(key == GLUT_KEY_UP )
    {
    	#ifdef DEBUG
    	cout << "UP key has been pressed.	Speed index of ball is " << ball_speed_index << endl;
    	#endif

    	if(ball_speed_index > -1){
    		circle[ball_speed_index].speed_up();

    		#ifdef DEBUG
    		cout << "Speed increased!" << endl;
    		#endif
    }

    }
    else if(key == GLUT_KEY_DOWN)
    {
    	#ifdef DEBUG
    	cout << "DOWN key has been pressed.	Speed index of ball is--" << " " << ball_speed_index << endl;
    	#endif

    	if(ball_speed_index > -1){
    		circle[ball_speed_index].speed_down();

    		#ifdef DEBUG
    		cout << "Speed Decreased!" << endl;
    		#endif

    	}
    }

}

/**
* Mouse input function
* @param state : state of the mouse click
* @param button : determines the selection of the button by the user
* @param x : state command from openGL
* @param y : state command from openGL
* co-ordinates the user inputs throught the mouse
*/
void mouse(int state, int button, int x, int y)
{

	float pos_x = x;
	float pos_y = y;

	mouse_x = pos_x;
	mouse_y = pos_y;

	for(int i = 0; i < circle.size(); i++)
	{
		if(check_selection(pos_x, pos_y, i))
		{
			ball_speed_index = i;
			ball_selected = true;

			#ifdef DEBUG
			cout << "Ball Has Been Selected " << endl;
			cout << "Index of the selected ball is : " << ball_speed_index << endl;
			#endif

			break;
		}

		else{
			ball_selected = false;
			ball_speed_index = -1;
		}
	}


}
