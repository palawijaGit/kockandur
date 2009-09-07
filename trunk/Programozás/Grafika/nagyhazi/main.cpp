#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std; 

void draw( void ) {
	glClear(GL_COLOR_BUFFER_BIT); 
	
	glBegin(GL_TRIANGLES);
	glVertex2f( 0.0f, 5.0f);
	glVertex2f( 5.0f, -3.0f);
	glVertex2f( -5.0f, -3.0f);
	glEnd();

	glFlush();
}

void initGL(int argc, char ** argv) {

	glutInit(&argc, argv); 
	glutInitWindowPosition(0,0); 
	glutInitWindowSize(500,500); 
	glutInitDisplayMode(GLUT_RGB);
	glutCreateWindow("Hello World!"); 

	glutDisplayFunc(draw); 

	glViewport(0, 0, 100, 100); 
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluOrtho2D( -10, 10, -10 , 10); 	
	glClearColor(0.2f, 0.0f, 0.0f, 0.0f);
	glColor3f(0.8f, 0.0f, 0.0f); 
}

int main(int argc, char ** argv) {
	
	initGL(argc, argv); 

	glutMainLoop();

	return 0; 
}
