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

/*
#include "main.h"


void printToConsole()
{
	// Print info
	std::cout << "OpenGL-Objects" << std::endl;

	std::cout << "\nAuthor:" << std::endl;
	std::cout << "    Georgi Baghdasaryan    baghdasaryan@ucla.edu" << std::endl;
}

// Create and send objects to the GPU
void initScene()
{
	cubes[0] = new Cube(100.0f, vec3(0.0f, 0.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), 0.2f, 0.6f, 0.2f, 100.0f, &camera, &light);
	cubes[0]->init("");

	// Set OpenGL parameters
	glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

// Draw the scene
void drawScene()
{
	// Draw the objects
	cubes[0]->draw(true, 0);		// bool => edges, number => mesh
}


// ----------------------------------Callback functions-----------------------------------------

void displayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawScene();

	glutSwapBuffers();
}

void keyboardCallback(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 033:				// Exit on ESC
	case 113:				// Exit on 'q'
	case 81:				// Exit on 'Q'
		//cleanUp();
		exit(0);
		break;
	case 32:				// reset default positioning on Space
		break;

	case 119:				// move camera up on 'w'
	case 87:				// move camera up on 'W'
		camera.vertical(0.01f);
		light.setPosition(camera.getPosition());
		break;
	case 115:				// move camera down on 's'
	case 83:				// move camera down on 'S'
		camera.vertical(-0.01f);
		light.setPosition(camera.getPosition());
		break;
	case 97:				// move camera left on 'a'
	case 65:				// move camera left on 'A'
		camera.horizontal(-0.01f);
		light.setPosition(camera.getPosition());
		break;
	case 100:				// move camera right on 'd'
	case 68:				// move camera right on 'D'
		camera.horizontal(0.01f);
		light.setPosition(camera.getPosition());
		break;
	case 'x':				// move camera forward on 'x'
	case 'X':				// move camera forward on 'X'
		camera.distance(-2.0f);
		break;
	case 'z':				// move camera backwards on 'z'
	case 'Z':				// move camera backwards on 'Z'
		camera.distance(2.0f);
		break;
	case 'r':				// reset camera position on 'r'
	case 'R':				// reset camera position on 'R'
		camera.reset();
		light.setPosition(camera.getPosition());
		break;
	case 'u':				// increase camera altitude on 'u'
	case 'U':				// increase camera altitude on 'U'
		camera.altitude(-0.5);
		light.setPosition(camera.getPosition());
		break;
	case 'j':				// decrease camera altitude on 'd'
	case 'J':				// decrease camera altitude on 'D'
		camera.altitude(0.5);
		light.setPosition(camera.getPosition());
		break;

	default:
		break;
	};

	// Set redisplay flag
	glutPostRedisplay();
}

void keyboardUpCallback(unsigned char key, int x, int y)
{
	// Set redisplay flag
	glutPostRedisplay();
}

void specialCallback(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_UP:			// negative rotation around X-axis
		break;
	case GLUT_KEY_DOWN:			// positive rotation around X-axis
		break;
	case GLUT_KEY_LEFT:			// rotate cubes left around Y-axis
		break;
	case GLUT_KEY_RIGHT:		// rotate cubes right around Y-axis
		break;
	default:
		break;
	};

	// Set redisplay flag
	glutPostRedisplay();
}

void specialUpCallback(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	default:
		break;
	};

	// Set redisplay flag
	glutPostRedisplay();
}

void reshapeCallback(int w, int h)
{
	// Store new window size information
	window_width = (w == 0) ? 1 : w;
	window_height = (h == 0) ? 1 : h;

	// Change the aspect ratio if the window is reshaped
	glViewport( 0, 0, w, h );
	//camera.updateAspect((GLfloat(w))/h);

	// Set redisplay flag
	glutPostRedisplay();
}

void idleCallback()
{	
	// Set redisplay flag
	glutPostRedisplay();
}

// ---------------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
	printToConsole();

	// Setup glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH |GLUT_MULTISAMPLE);
	glutInitWindowSize(window_width, window_height);
	//glutInitContextVersion(3, 2);
	//glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("OpenGL-Objects");

	// Setup glew
	glewExperimental = GL_TRUE;
	glewInit();

	// Initialize objects
	initScene();

	// Setup callback functions
	glutDisplayFunc(displayCallback);
	glutKeyboardFunc(keyboardCallback);
	glutKeyboardUpFunc(keyboardUpCallback);
	glutSpecialFunc(specialCallback);
	glutSpecialUpFunc(specialUpCallback);
	glutReshapeFunc(reshapeCallback);
	glutIdleFunc(idleCallback);

	glutMainLoop();
	return 0;
}*/



























































#include <iostream>
#include "Angel.h"
#include <math.h>

const int numCubes = 8;
const float cubeDims = 5.0;
const float distOrigin = 10.0;
const float crossHairLoc = 1.0;

vec4 cubeLocs[numCubes];	// Centers of cubes

// Vertices for a cube located at the origin
const int numVertices = 8;
vec4 cubeVertices[numVertices];

// Points for drawing cubes: (6 faces/cube)(2 triangles/face)(3 vertices/triangle)
const int numTrianglePoints = 36;
vec4 points[numTrianglePoints];

// Points for drawing cubes using a single triangle strip
const int numPointStrip = 14;
vec4 pointStrip[numPointStrip + 2];		// 2 empty buckets

// Points for drawing cube edges: (12 edges/cube)(2 vertices/edge)
const int numEdges = 24;
vec4 cubeEdges[numEdges];

// Points for drawing a Cross-Hair
const int numCrossHair = 4;
vec4 crossHair[numCrossHair];

vec4 colors[numCubes] = {		// Each cube will have a different color
	vec4(0.0, 0.0, 0.0, 1.0),	// black
    vec4(1.0, 0.0, 0.0, 1.0),	// red
    vec4(1.0, 1.0, 0.0, 1.0),	// yellow
    vec4(0.0, 1.0, 0.0, 1.0),	// green
    vec4(0.0, 0.0, 1.0, 1.0),	// blue
    vec4(1.0, 0.0, 1.0, 1.0),	// magenta
	vec4(1.0, 0.5, 0.0, 1.0),	// orange
    vec4(0.0, 1.0, 1.0, 1.0)	// cyan
};
int colorOffset = 0;

// Viewing transformation parameters
GLfloat idleRotate = 0.0; 
GLfloat theta = 0.0;	// altitude
GLfloat phi = 0.0;		// azimuth
vec4 cameraPos = vec4(0.0, 0.0, 56.0, 1.0);

// Projection transformation parameters
GLfloat  fovy = 45.0;
GLfloat  aspect;
GLfloat  zNear = 0.1, zFar = 1000.0;

// Uniform variables
GLuint  projection;
GLuint  model_view;
GLuint cubeColor;

// Additional options
bool crossHairOn = false;
bool edgesOn = false;
bool idleRotateOn = false;
bool singleStripOn = false;

// Helping variables
int index = 0;

void genPoints(vec4 *out, int a, int b, int c, int d, bool faceTriangles)
{
	if(faceTriangles)
	{
		out[index++] = cubeVertices[a];
		out[index++] = cubeVertices[b];
		out[index++] = cubeVertices[c];
		out[index++] = cubeVertices[a];
		out[index++] = cubeVertices[c];
		out[index++] = cubeVertices[d];
	}
	else
	{
		out[index++] = cubeVertices[a];
		out[index++] = cubeVertices[b];
		out[index++] = cubeVertices[c];
		out[index++] = cubeVertices[d];
	}
}

void genVertices(vec4 *out, float size, bool crossHair)
{
	if(!crossHair)
	{
		out[0] = vec4(-size, -size, size, 1.0);
		out[1] = vec4(-size, size, size, 1.0);
		out[2] = vec4(size, size, size, 1.0);
		out[3] = vec4(size, -size, size, 1.0);
		out[4] = vec4(-size, -size, -size, 1.0);
		out[5] = vec4(-size, size, -size, 1.0);
		out[6] = vec4(size, size, -size, 1.0);
		out[7] = vec4(size, -size, -size, 1.0);
	}
	else
	{
		out[0] = vec4(-size, 0.0, 0.0, 1.0);
		out[1] = vec4(size, 0.0, 0.0, 1.0);
		out[2] = vec4(0.0, -size, 0.0, 1.0);
		out[3] = vec4(0.0, size, 0.0, 1.0);
	}
}

void cubePrep()
{
	// generate locations for centers of 8 cubes
	genVertices(cubeLocs, distOrigin, false);

	// generate vertices for a cube with cubeSide located at the origin
	genVertices(cubeVertices, cubeDims/2.0, false);

	// generate points for cross-hair
	genVertices(crossHair, crossHairLoc, true);

	// generate points for triangle faces (usual method: 36 points)
	index = 0;
	genPoints(points, 1, 0, 3, 2, true);
	genPoints(points, 2, 3, 7, 6, true);
	genPoints(points, 3, 0, 4, 7, true);
	genPoints(points, 6, 5, 1, 2, true);
	genPoints(points, 4, 5, 6, 7, true);
	genPoints(points, 5, 4, 0, 1, true);
	
	// generate points for triangle faces (triangle strip method: 14 points)
	index = 0;
	genPoints(pointStrip, 1, 2, 0, 3, false);
	genPoints(pointStrip, 7, 2, 6, 1, false);
	genPoints(pointStrip, 5, 0, 4, 7, false);
	genPoints(pointStrip, 5, 6, 0, 0, false);
	
	// generate points for drawing edges
	index = 0;
	genPoints(cubeEdges, 0, 1, 1, 2, false);
	genPoints(cubeEdges, 2, 3, 3, 0, false);
	genPoints(cubeEdges, 0, 4, 4, 5, false);
	genPoints(cubeEdges, 5, 6, 6, 7, false);
	genPoints(cubeEdges, 7, 4, 1, 5, false);
	genPoints(cubeEdges, 2, 6, 3, 7, false);
}

void init()
{
	cubePrep();		// prepare data for cube(s)

	// Create a vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

	 // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(pointStrip) + sizeof(cubeEdges) + sizeof(crossHair), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(pointStrip), pointStrip);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(pointStrip), sizeof(cubeEdges), cubeEdges);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(pointStrip) + sizeof(cubeEdges), sizeof(crossHair), crossHair);

    // Load shaders and use the resulting shader program
    GLuint program = InitShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    // Set up vertex arrays
    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	// Bind uniform variables to shaders
	model_view = glGetUniformLocation(program, "model_view");
	projection = glGetUniformLocation(program, "projection");
	cubeColor = glGetUniformLocation(program, "color");

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0); 
}



void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set perspective projection
	mat4  persp = Perspective(fovy, aspect, zNear, zFar);
	glUniformMatrix4fv(projection, 1, GL_TRUE, persp);

	mat4  mv;
	for(int i = 0; i < numCubes; i++)
	{
		// Set translations, rotations, and camera position
		mv = RotateY(phi) * RotateX(theta) * Translate(-cameraPos) * Translate(cubeLocs[i]) * RotateZ(idleRotate);
		glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);

		// Draw cube edges
		if(edgesOn)
		{
			glUniform4fv(cubeColor, 1, colors[0]);
			glDrawArrays(GL_LINES, numTrianglePoints + numPointStrip + 2, numEdges);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(0.5, 0.5);
		} 

		// Set cube color
		glUniform4fv(cubeColor, 1, colors[(numCubes - i + colorOffset)%8]);

		if(singleStripOn)
			glDrawArrays(GL_TRIANGLE_STRIP, numTrianglePoints, numPointStrip);
		else
			glDrawArrays(GL_TRIANGLES, 0, numTrianglePoints);
	}

	// Display a cross-hair
	if(crossHairOn)
	{
		// switch to orthogonal perspective
		mv = mat4();
		persp = mat4();
		glUniform4fv(cubeColor, 1, colors[0]);
		glUniformMatrix4fv(projection, 1, GL_TRUE, persp);
		glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);
		glDrawArrays(GL_LINES, numTrianglePoints + numPointStrip + 2 + numEdges, numCrossHair);
	}

	glutSwapBuffers();
}

void callbackKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 113:				// Exit on 'q'
	case 81:				// Exit on 'Q'
		exit(0);
		break;
	case 99:				// Cycle colors on 'c'
	case 67:				// Cycle colors on 'C'
		colorOffset += 1;
		break;
	case 105:				// move camera forward on 'i'
	case 73:				// move camera forward on 'I'
		cameraPos.z -= 0.25;
		break;
	case 106:				// move camera left on 'j'
	case 74:				// move camera left on 'J'
		cameraPos.x += 0.25;
		break;
	case 107:				// move camera right on 'k'
	case 75:				// move camera right on 'K'
		cameraPos.x -= 0.25;
		break;
	case 109:				// move camera backwards on 'm'
	case 77:				// move camera backwards on 'M'
		cameraPos.z += 0.25;
		break;
	case 32:				// Reset default settings on Space
		theta = 0.0;
		phi = 0.0;
		cameraPos = vec4(0.0, 0.0, 56.0, 1.0);
		break;
	case 110:				// narrower field of view on 'n'
	case 78:				// narrower field of view on 'N'
		aspect /= 0.95;
		break;
	case 119:				// wider field of view on 'w'
	case 87:				// wider field of view on 'W'
		aspect *= 0.95;
		break;
	case 120:				// display cross-hair on 'x'
	case 88:				// display cross-hair on 'X'
		crossHairOn = !crossHairOn;
		break;
	case 115:				// turn single strip implementation on/off on 's'
	case 83:				// turn single strip implementation on/off on 'S'
		singleStripOn =!singleStripOn;
		break;
	case 114:				// start/stop cube rotation on 'r'
	case 82:				// start/stop cube rotation on 'R'
		idleRotateOn = !idleRotateOn;
		idleRotate = 0;
		break;
	case 101:				// show/hide cube edges on 'e'
	case 69:				// show/hide cube edges on 'E'
		edgesOn = !edgesOn;
		break;
	default:
		break;
	};

	// Set redisplay flag
	glutPostRedisplay();
}

void callbackSpecial(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_UP:		// Altitudal view -> up
		theta -= 1.0;
		break;
	case GLUT_KEY_DOWN:		// Altitudal view -> down
		theta += 1.0;
		break;
	case GLUT_KEY_LEFT:		// Azimuthal view -> left
		phi -= 1.0;
		break;
	case GLUT_KEY_RIGHT:	// Azimuthal view -> right
		phi += 1.0;
		break;
	};

	// Set redisplay flag
	glutPostRedisplay();
}

void callbackReshape(int width, int height)
{
	// Change the aspect ratio if the window is reshaped
    glViewport(0, 0, width, height);
    aspect = GLfloat((width)/height);
}

void callbackIdle()
{
	// Rotate cubes on idle on selected option
	if(idleRotateOn)
	{
		idleRotate += 0.3;
		if(idleRotate >= 360.0)
		{
			idleRotate -= 360.0;
		}

		// Set redisplay flag
		glutPostRedisplay();
	}
}

// Display instructions
void printInstructions()
{
	std::cout << "Instructions:" << std::endl;
	std::cout << "    Press 'q' or 'Q' to exit the program." << std::endl;
	std::cout << "    Press 'c' or 'C' to cycle the color of all cubes." << std::endl;
	std::cout << "    Press Arrow Up to increase altitude." << std::endl;
	std::cout << "    Press Arrow Down to decrease altitude." << std::endl;
	std::cout << "    Press Arrow Left to decrease azimuth." << std::endl;
	std::cout << "    Press Arrow Right to increase azimuth." << std::endl;
	std::cout << "    Press 'i' or 'I' to move camera forward." << std::endl;
	std::cout << "    Press 'j' or 'J' to move camera left." << std::endl;
	std::cout << "    Press 'k' or 'K' to move camera right." << std::endl;
	std::cout << "    Press 'm' or 'M' to move camera backwards." << std::endl;
	std::cout << "    Press Space to reset view to the starting position." << std::endl;
	std::cout << "    Press 'n' or 'N' for narrower field of view." << std::endl;
	std::cout << "    Press 'w' or 'W' for wider field of view." << std::endl;
	std::cout << "    Press 'x' or 'X' to show/hide a cross-hair." << std::endl;
	std::cout << "    Press 's' or 'S' to turn on/off single strip implementation." << std::endl;
	std::cout << "    Press 'r' or 'R' to start/stop rotating cubes." << std::endl;
	std::cout << "    Press 'e' or 'E' to show/hide cube edges." << std::endl;
}

int main(int argc, char **argv)
{
	printInstructions();

	// Setup glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	//glutInitContextVersion(3, 2);
	//glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Assignment #2");

	// Setup glew
	glewExperimental = GL_TRUE;
	glewInit();

	// Create points and send them to buffer
	init();

	// Setup callback functions
	glutDisplayFunc(display);
	glutKeyboardFunc(callbackKeyboard);
	glutSpecialFunc(callbackSpecial);
	glutReshapeFunc(callbackReshape);
	glutIdleFunc(callbackIdle);
	
	glutMainLoop();
	return 0;
}







//// Input: angle (degrees), rotation coordinates
//vec4 createQuaternion(float x, float y, float z, double angle)
//{
//	// convert angle to radians
//	angle *= (M_PI/180);
//
//	// Normalize quaternion (if necessary)
//	double magnitude = angle*angle + x*x + y*y + z*z; 
//	if(0.9 < magnitude || magnitude > 1.1) //0.9 and 0.11 since we are using floating points
//	{
//		magnitude = sqrtf(magnitude);
//		angle /= magnitude;
//		x /= magnitude;
//		y /= magnitude;
//		z /= magnitude;
//	}
//	return vec4(x, y, z, angle);
//}
//
//// multiply two quaternions (do not pass in rotated quaternions)
//vec4 multQuaternions(vec4 quat1, vec4 quat2)
//{
//	vec4 result;
//	result.x = quat1.w*quat2.x + quat1.x*quat2.w + quat1.y*quat2.z - quat1.z*quat2.y;
//	result.y = quat1.w*quat2.y - quat1.x*quat2.z + quat1.y*quat2.w + quat1.z*quat2.x;
//	result.z = quat1.w*quat2.z + quat1.x*quat2.y - quat1.y*quat2.x + quat1.z*quat2.w;
//	result.w = quat1.w*quat2.w - quat1.x*quat2.x - quat1.y*quat2.y - quat1.z*quat2.z;
//	return result;
//}
//
//// generate a quarternion rotation matrix
//vec4 rotateQuarternion(vec4 quat)
//{
//	vec4 rotation;
//	rotation.x = quat.x * sinf(quat.w/2.0);
//	rotation.y = quat.y * sinf(quat.w/2.0);
//	rotation.z = quat.z * sinf(quat.w/2.0);
//	rotation.w = cosf(quat.w/2.0);
//	return rotation;
//}
//
//// generate rotation matrix from quarternion (to multiply with model_view)
//mat4 generateRotationMatrix(vec4 quat)
//{
//	mat4 result;
//	result[0] = vec4(quat.w*quat.w + quat.x*quat.x - quat.y*quat.y - quat.z*quat.z, 2*quat.x*quat.y - 2*quat.w*quat.z, 2*quat.x*quat.z + 2*quat.w*quat.y, 0.0);
//	result[1] = vec4(2*quat.x*quat.y + 2*quat.w*quat.z, quat.w*quat.w - quat.x*quat.x + quat.y*quat.y - quat.z*quat.z, 2*quat.y*quat.z + 2*quat.w*quat.x, 0.0);
//	result[2] = vec4(2*quat.x*quat.z + 2*quat.w*quat.y, 2*quat.y*quat.z - 2*quat.w*quat.x, quat.w*quat.w - quat.x*quat.x - quat.y*quat.y + quat.z*quat.z, 0.0);
//	result[3] = vec4(0.0, 0.0, 0.0 , 1.0);
//	return result;
//}