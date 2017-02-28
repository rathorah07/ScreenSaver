#include "Circle.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "Variable.h"
#include <iostream>
using namespace std;

Circle :: Circle(){

	para = 0; //Speed parameter
	mass = 1.0;
	pos[0] = 0; pos[1] = 0;
	vel[0] = 0; vel[1] = 0;
	radius = 50;
	color[1] = 0;color[2] = 0;color[3] = 0;

}

void Circle :: speed_up(){

	if (fabs(vel[0]) < para*10)
	{
		if(vel[0] >= 0)
			vel[0] += para;
		else
			vel[0] -= para;
	}

	else
		vel[0] = para*10;


	if(fabs(vel[1]) < para*10)
	{
		if(vel[1] >= 0)
			vel[1] += para;
		else
			vel[1] -= para;
	}

	else
	vel[1]=para*10;

	#ifdef DEBUG
	cout << "Speed uniformly increased in both directions" << endl;
	#endif

}

void Circle :: speed_down(){

	if(fabs(vel[0]) > para)
	{
		if(vel[0] >= 0)
			vel[0] -= para;
		else
			vel[0] += para;
	}

	else
		vel[0] = 0;


	if(fabs(vel[1]) > para)
	{
		if(vel[1] >= 0)
			vel[1] -= para;
		else
			vel[1] += para;
	}

	else
		vel[1] = 0;

	#ifdef DEBUG
	cout << "Speed decresed uniformly in both directions" << endl;
	#endif

}

void Circle :: create_circle(){

	GLfloat x1 = 0.0, y1 = 0.0;

	glColor3f(color[0],color[1],color[2]);
	glBegin(GL_POLYGON);

	for(int i = 0;i < 720; i++)
	{
		x1 = pos[0] + radius * sin(2 * PI * i / 720);
		y1 = pos[1] + radius * cos(2 * PI * i / 720);

		glVertex2f(x1,y1);
	}
	glFlush();
	glEnd ();
}

void Circle :: move_circle(int Width, int Height){

	if ((pos[0] + radius >= Width) || (pos[0] - radius <= 0))
	{
		vel[0] = -vel[0];
		#ifdef DEBUG
		cout << "Collision with wall in X direction" << endl;
		#endif
	}

	if((pos[1] + radius >= Height) || (pos[1] - radius <= 50))
	{
		vel[1] = -vel[1];
		#ifdef DEBUG
		cout << "Collision with wall in Y direction" << endl;
		#endif
	}

	pos[0] = pos[0] + vel[0];
	pos[1] = pos[1] + vel[1];

}
