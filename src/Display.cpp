#include "Display.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Variable.h"
#include <sstream>
/**
* Display Function : This Function is called by the main Function using the glutDisplayFunc() Function. This function creates and manages
*  threads at each time frame. It also controls the menu bar on top of the screen.
*/


void display(){

	glClear(GL_COLOR_BUFFER_BIT);

	if(!paused){

		int  index[thread.size()]; ///<  Variables to send thread number void pointers.

		for(int i = 0; i < thread.size(); i++)
		{
			index[i] = i;
			pthread_create(&thread[i], NULL, thread_func, (void*)&index[i]); ///< Creates threads for each ball.
		}


		for(int i = 0; i < thread.size(); i++)
			pthread_join(thread[i], NULL);		///< Waits for all threads to finish.

		while(!mein.empty())
			mein.pop();

		while(!meout.empty())
			meout.pop();

		for(int i = 0; i < circle.size(); i++)
			circle[i].create_circle();		///< Draw the circle on the screen.


		glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_POLYGON);
		glVertex2f(0,0);
		glVertex2f(0,50);
		glVertex2f(Width,50);   // get window width
		glVertex2f(Width,0);
		glFlush();
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glRasterPos2f(7.5, 32.5);

		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char* ) "Press Space Bar to pause the Screen Saver"); ///< Menu Bar

		glutSwapBuffers();
		glutPostRedisplay();

	}

	else{

		int index[thread.size()];

		for(int i = 0; i < thread.size(); i++)
			circle[i].create_circle();

		int drawn = 0;

		glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_POLYGON);
		glVertex2f(0,0);
		glVertex2f(0,50);
		glVertex2f(Width,50);
		glVertex2f(Width,0);
		glFlush();
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glRasterPos2f(7.5, 32.5);

		if (ball_speed_index == -1){
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char* ) "Click on a ball to select it");
		}

		else{
			std :: ostringstream oss;
			oss << "Selected Ball : Position in x = " << circle[ball_speed_index].pos[0] << "; Position in y = " << circle[ball_speed_index].pos[1] << "; Velocity in x = " << circle[ball_speed_index].vel[0] << "; Velocity in y = " << circle[ball_speed_index].vel[1];
			std :: string ostring = oss.str();
			const char* output = new char[300];
			output = ostring.c_str();
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char* ) output);
		}


		glutSwapBuffers();
		glutPostRedisplay();
	}

}

/**
* Reshape Function : Controls the reshaping of the window.
*/


void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (0.0, (GLdouble) w,(GLdouble) h,0.0);
	Width =w;
	Height = h;
}

/**
* Reshape Function : Initializes the OpenGL state
*/


void init(void){
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double w = glutGet( GLUT_WINDOW_WIDTH );
 	double h = glutGet( GLUT_WINDOW_HEIGHT );
    glOrtho(0.0,w,h,0.0,-1.0,1.0);
}
