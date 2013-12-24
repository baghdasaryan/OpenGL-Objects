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


#endif  // __MAIN_H__
