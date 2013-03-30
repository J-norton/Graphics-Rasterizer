#include <iostream>
#include "Sphere.h"
#include "World.h"
#include "GeometricObj.h"
#include <glut.h>


#define NUM_X_PIXELS 512
#define NUM_Y_PIXELS 512

void mainLoop(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	Sphere &s = Sphere(16, 32);
	World scene = World();
	scene.addObject(s);

	//==========================================GRADING AREA================================================================

	//scene.transformPartA();
	
	//scene.transformPartB();

	//scene.transformPartC();

	scene.transformPartD();

	//==========================================END OF GRADING AREA================================================================ 
	
	float* raw_pixels = new float[X_PIXELS * Y_PIXELS * 3];
	scene.writePixels(raw_pixels);
	glDrawPixels(NUM_X_PIXELS, NUM_Y_PIXELS, GL_RGB, GL_FLOAT, raw_pixels);
	glutSwapBuffers();

	delete[] raw_pixels;
}


int main(int a, char** c)
{
	glutInit(&a, c);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(NUM_X_PIXELS, NUM_Y_PIXELS);

	glClearColor(1.0, 0.0, 0.0, 0.0);

	glutCreateWindow("My Window");
	glutDisplayFunc(mainLoop);

	glutMainLoop();
	return 0;
}