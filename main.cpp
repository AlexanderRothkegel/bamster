// vim: set ts=4 sw=4 expandtab sts=4:
#include <iostream>
#include <X11/Xlib.h>
#include <GL/glut.h>

#include "imageloader.h"

const unsigned int elapsedUSecs = 40;
int hamsterPos=0;

void handelKeypress(unsigned char key, int x, int y) {
    switch (key):
        case 27: //Escape
            exit(0);
    }

using std::cout;
GLsizei wh = 250 ;
GLsizei ww = 250 ;
//dot.cpp
// initial height of window
// initial width of window
void Displaydot ( void );
void MyInit
( );

unsigned int counter = 0;

void Displaydot ( void ) {
glClear ( GL_COLOR_BUFFER_BIT ); //clear pixel buffer
glBegin(GL_POINTS);
// render with points
glVertex2i(hamsterPos,210); //display a point
glEnd();
glFlush();
}


void MyInit ( void ) {
cout << glGetString(GL_VERSION) <<"\n";
cout << glGetString(GL_VENDOR) <<"\n";
glClearColor ( 1.0, 1.0, 1.0, 0.0 ); //white background
glColor3f(0.0f, 1.0f,0.0f);
// green drawing colour
glPointSize(10.0);
// 10 pixel dot!
glMatrixMode ( GL_PROJECTION );
glLoadIdentity ( );
gluOrtho2D ( 0.0, (GLdouble)ww, 0.0, (GLdouble)wh ); //Display area
}



void handleKeypress (unsigned char key, int x, int y) 

{
	switch (key) {
		case 27:
//			cleanup();
			exit(0);
	}
}



struct keyLogger {
	bool leftKey;
	bool rightKey;
	bool upKey;

} pressedKeys ;

void timerCallback (int value) 
{ 
	glClear ( GL_COLOR_BUFFER_BIT ); //clear pixel buffer
	glBegin(GL_POINTS);
	// render with points
	glColor3f(0.0f, 1.0f,0.0f);
	glVertex2i(counter%100,210); //display a point
	//interface.plot();
	//map.plot();
	//player.plot();
	//
	if (pressedKeys.leftKey == true)
		counter--;
	if (pressedKeys.rightKey == true)
		counter++;

	glEnd();
	glFlush();
    /* Do timer processing */
    /* maybe glutPostRedisplay(), if necessary */
    /* call back again after elapsedUSecs have passed */
    glutTimerFunc (elapsedUSecs, timerCallback, value); 
}


void handleSpecialKeyReleased(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT:
			pressedKeys.leftKey = false;
			break;
		case GLUT_KEY_RIGHT:
			pressedKeys.rightKey = false;
			break;
		case GLUT_KEY_UP:
			pressedKeys.upKey = false;
	}
}



void handleSpecialKeypress(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT:
			pressedKeys.leftKey = true;
			break;
		case GLUT_KEY_RIGHT:
			pressedKeys.rightKey = true;
			break;
		case GLUT_KEY_UP:
			pressedKeys.upKey = true;
			break;
	}
}







int main(int argc, char **argv) {
glutInit( &argc, argv );
glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
glutInitWindowSize
( ww, wh );
// window size
glutInitWindowPosition
( 180, 90 ); // & position on screen
glutCreateWindow
( "Display a Dot" );
MyInit ( );
glutDisplayFunc ( Displaydot );
glutTimerFunc ( 40,timerCallback,1 ) ;
	glutKeyboardFunc(handleKeypress);
	glutSpecialFunc(handleSpecialKeypress);
	glutSpecialUpFunc(handleSpecialKeyReleased);
glutMainLoop ( );






return 0;
}

