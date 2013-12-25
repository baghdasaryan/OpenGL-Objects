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

#include "Windows.h"
#include "Angel.h"
#include "Camera.h"
#include "Light.h"

// Objects
#include "Rectangle.h"

// Global variables
int window_width = 512;
int window_height = 512;
GLfloat fovy = 5.0;
GLfloat zNear = 0.1;
GLfloat zFar = 10000.0;
Camera camera = Camera(128.0, 6.0, zNear, zFar, fovy);
Light light = Light(camera.getPosition(), vec4(1.0, 1.0, 1.0, 1.0));

// Function declarations
void printInstructions();
void initScene();
void drawScene();

// Callback functions
void displayCallback();
void keyboardCallback(unsigned char key, int x, int y);
void keyboardUpCallback(unsigned char key, int x, int y);
void specialCallback(int key, int x, int y);
void specialUpCallback(int key, int x, int y);
void reshapeCallback(int w, int h);
void idleCallback();

// Timing
double TIME;
double TIME_LAST;
double DTIME;
double FRAME_TIME = 0;
int FRAME_COUNT = 0;

double MONSTER_TIME = 0;

// Objects
Cube *cubes[2];

bool soundOn = false;

#endif  // __MAIN_H__
