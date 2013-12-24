// ############################################ //
// ############################################ //
// ####                                    #### //
// ####    Program: OpenGL-Objects         #### //
// ####    Language: C++                   #### //
// ####    Author: Georgi Baghdasaryan     #### //
// ####    Email: baghdasaryan@ucla.edu    #### //
// ####                                    #### //
// ############################################ //
// ############################################ //


#ifndef __MAIN_H__
#define __MAIN_H__

#include "Angel.h"
#include "Rectangle.h"
#include "Camera.h"
#include "Light.h"



// Function declarations
void printToConsole();

// Callback functions
void displayCallback();
void keyboardCallback(unsigned char key, int x, int y);
void keyboardUpCallback(unsigned char key, int x, int y);
void specialCallback(int key, int x, int y);
void specialUpCallback(int key, int x, int y);
void reshapeCallback(int w, int h);
void idleCallback();


// Constants
int window_width = 512;
int window_height = 512;
GLfloat fovy = 5.0;
GLfloat zNear = 0.1;
GLfloat zFar = 10000.0;
Camera camera = Camera(10.0, 90.0, zNear, zFar, fovy);
Light light = Light(camera.getPosition(), vec4(1.0, 1.0, 1.0, 1.0));


Cube *cubes[1];

#endif  // __MAIN_H__
