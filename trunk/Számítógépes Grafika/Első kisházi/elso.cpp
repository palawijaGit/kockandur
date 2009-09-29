//========================================================
// Hazi feladat keret.          
// A //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// sorokon beluli reszben celszeru garazdalkodni, mert
// a tobbit ugyis toroljuk. 
// A Hazi feladat csak ebben a fajlban lehet
// Tilos:
// - mast "beincludolni", illetve mas konyvtarat hasznalni
// - faljmuveleteket vegezni
//========================================================

#include <math.h>
#include <stdlib.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
// MsWindows-on ez is kell
#include <windows.h>     
#endif // Win32 platform

#include <GL/gl.h>
#include <GL/glu.h>
// A GLUT-ot le kell tolteni: http://www.opengl.org/resources/libraries/glut/
#include <GL/glut.h>     

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Innentol modosithatod...

//--------------------------------------------------------
// Nev: Matyas-Peti Csaba
// Neptun: PVD8VB
//--------------------------------------------------------

class Vector {
	private: 
		float x,y,z;
	public: 
		Vector(float x = 0.0, float y = 0.0, float z = 0.0): x(x), y(y), z(z) {}; 
		Vector(const Vector &v) {x = v.x; y = v.y; z = v.z;}
		const float getX(void) const {return x;}
		const float getY(void) const {return y;} 
		const float getZ(void) const {return z;} 
		Vector operator*(float mult) const { return Vector(x*mult, y*mult, z*mult); }
		const float operator*(const Vector & v) {return x*v.x + y * v.y + z*v.z;}
		const float abs() const { return sqrt(x*x + y*y + z*z); }
};

void onInitialization( ) { 
}

void onDisplay( ) {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ...

    // Buffercsere: rajzolas vege
    glFinish();
    glutSwapBuffers();
}

void onMouse(int button, int state, int x, int y) {
    // A GLUT_LEFT_BUTTON / GLUT_RIGHT_BUTTON
    // ill. a GLUT_DOWN / GLUT_UP makrokat hasznald.
}

void onIdle( ) {
}

void onKeyboard(unsigned char key, int x, int y) {
}

// ...Idaig modosithatod
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(int argc, char **argv) {
    glutInit(&argc, argv); 
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Grafika hazi feladat");

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    onInitialization();

    glutDisplayFunc(onDisplay);
    glutMouseFunc(onMouse); 
    glutIdleFunc(onIdle);
    glutKeyboardFunc(onKeyboard);

    glutMainLoop();
    
    return 0;    
}
