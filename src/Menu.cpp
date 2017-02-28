#include "Menu.h"
#include "Variable.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
using namespace std;

/**
* Menu Handling function
* This function handles all the menu operations as and when called by the user
*/
void menu(int item)
{
        /**
        * Switch command
        */
        switch (item)
        {
        case MENU_FRONT:
        	{
                        /**
                        * This menu command pauses / plays the system as per state of the system.
                        */
        		show = (MENU_TYPE) item;
                        #ifdef DEBUG
        		cout << "System Paused/Played " << endl;
                        #endif

        		if (!paused){
        			paused = true;
        		}

        		else{
        			paused = false;
        		}
        	}
        	break;

        case MENU_SPOT:
        	{
                        /**
                        * This menu command changes the color randomly of the selected ball only if the system is
                        * paused.
                        */
        		show = (MENU_TYPE) item;
        		if (ball_speed_index != -1 && paused){

                                #ifdef DEBUG
                                cout << "Selected ball index : " << ball_speed_index << endl;
        			#endif

					circle[ball_speed_index].color[0] = 0.1*(rand()%10);
					circle[ball_speed_index].color[1] = 0.1*(rand()%10);
					circle[ball_speed_index].color[2] = 0.1*(rand()%10);

                                #ifdef DEBUG
                                cout << "Colour of ball the selected is changed" << endl;
                                #endif

        		}
        	}
        	break;

        case MENU_BACK_RIGHT:
        	{
                        /**
                        * This menu command adds a new ball to the system only if the system is paused and no ball is
                        * selected.
                        */
        			show = (MENU_TYPE) item;
        			if (!ball_selected && paused){

                                        #ifdef DEBUG
        				cout << "Creating a new Ball" << endl;
                                        #endif

        				num_balls++;
        				circle.resize(num_balls);
        				thread.resize(num_balls);
        				//! initializing the ball

        				circle[circle.size() - 1].pos[0] = mouse_x;
        				circle[circle.size() - 1].pos[1] = mouse_y;

        				//! randomizing the velocity
        				int velsetx = rand() % 2;
						int velsety = rand() % 2;

						circle[circle.size() - 1].para = 0.4;
						float para = circle[circle.size() - 1].para;
						circle[circle.size() - 1].vel[0] =  para*velsetx*(rand() % (11));
						circle[circle.size() - 1].vel[1] =  para*velsety*(rand() % (11));

        				//! randomizing the color of the circle
        				circle[circle.size() - 1].color[0] = 0.1*(rand()%10);
						circle[circle.size() - 1].color[1] = 0.1*(rand()%10);
						circle[circle.size() - 1].color[2] = 0.1*(rand()%10);

						//! randomizing the radius
						circle[circle.size() - 1].radius = 5*(rand() % 5+2);
						float maxr= circle[circle.size() - 1].radius;

							for(int i = 0; i < counter; i++)
							{
								float centre_distance = (((circle[i].pos[0] - circle[circle.size() - 1].pos[0])*(circle[i].pos[0] - circle[circle.size() - 1].pos[0])) + ((circle[i].pos[1] - circle[circle.size() - 1].pos[1])*(circle[i].pos[1] - circle[circle.size() - 1].pos[1])));
								if(centre_distance <= (circle[i].radius + circle[circle.size() - 1].radius)*(circle[i].radius + circle[circle.size() - 1].radius))
								{
									maxr = min((double)maxr , (sqrt(centre_distance) - circle[i].radius));
								}

							}


								if (circle[circle.size() - 1].pos[0] + circle[circle.size() - 1].radius >= Width)
									maxr = min(maxr, Width - circle[circle.size() - 1].pos[0]);

								if (circle[circle.size() - 1].pos[0] - circle[circle.size() - 1].radius <= 0)
									maxr = min(maxr, circle[circle.size() - 1].pos[0]);

								if (circle[circle.size() - 1].pos[1] + circle[circle.size() - 1].radius >= Height)
									maxr = min(maxr, Height - circle[circle.size() - 1].pos[1]);

								if (circle[circle.size() - 1].pos[1] - circle[circle.size() - 1].radius <= 50)
									maxr = min(maxr, circle[circle.size() - 1].pos[1] - 50);

						counter++;
						circle[circle.size() - 1].radius = maxr;
						circle[circle.size() - 1].mass = (circle[circle.size() - 1].radius)*36 + 1;

                                                #ifdef DEBUG
                                                cout << "New ball added!!" << endl;
                                                #endif

        			}
        	}
        	break;

        case MENU_BACK_LEFT:
        	{
                                /**
                                * This menu command removes the selected ball from the system when it is paused.
                                */
        			show = (MENU_TYPE) item;
        			if (ball_speed_index != -1 && paused){

                                        #ifdef DEBUG
                                        cout << "Selected ball index : " << ball_speed_index << endl;
        				cout << "Deleting Selected Ball" << endl;
                                        #endif

        				vector<Circle>::iterator iter = circle.begin();

        				for (int i = 0; i < ball_speed_index; i++){
        						iter++;
        				}

        				circle.erase(iter);
        				num_balls--;
        				counter--;
        				circle.resize(num_balls);
        				thread.resize(num_balls);

                                        #ifdef DEBUG
                                        cout << "Selected ball deleted!!" << endl;
                                        #endif
        			}
        	}
        	break;

        default:
                {       /**
                        * Default menu command
                        */
                }
                break;
        }

        glutPostRedisplay();

        return;
}
