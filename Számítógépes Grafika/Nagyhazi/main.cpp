#include <GL/glut.h>
#include <QImage>

void gl_init() {
	glViewport(0.0, 0.0, 1.0, 1.0); 
	glMatrixMode(GL_PROJECTION);
}

void gl_loop() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glutSwapBuffers(); 
}

int main(int argc, char ** argv) {
	QImage proba("proba.jpg");
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); 
	glutCreateWindow("PVD8VB Nagyházi"); 
	glutIdleFunc(gl_loop); 
	glutFullScreen();
	glutMainLoop(); 
	return 0;
}
