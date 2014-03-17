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


#ifndef __GLUTILS_H__
#define __GLUTILS_H__

#include <iostream>
#include <fstream>
#include <cstdlib>

#ifdef __APPLE__  // Apple 
#  include <OpenGL/OpenGL.h>
#  include <GLUT/glut.h>
#elif __linux__ // Linux 
#  include "GL/glew.h"
#  include "GL/freeglut.h"
#else // Windows
#  include <windows.h> 
#  include "GL/glew.h"
#  include "GL/freeglut.h"
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef DEGREES_TO_RADIANS
#define DEGREES_TO_RADIANS 0.01745329251994329576922222222222	// Same as (M_PI / 180.0f)
#endif

#ifndef GRAVITY_ACC
#define GRAVITY_ACC 9.80665
#endif

// Blah blah blah
namespace GLutils
{
	GLuint InitShader(const char* vShaderFile, const char* fShaderFile);
}

using namespace GLutils;

#endif  // __GLUTILS_H__