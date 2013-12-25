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
	cubes[0] = new Cube(1.0f, vec3(0.0f, 1.5f, 3.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), 0.2f, 0.6f, 0.2f, 100.0f, &camera, &light);
	cubes[0]->init("");

	// Set OpenGL parameters
	glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

// Draw the scene
void drawScene()
{
	// Draw the objects
	cubes[0]->draw(true, 0);		// bool => edges, number => mesh
}

// Clean up
void cleanUp()
{
	delete cubes[0];
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
		cleanUp();
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
		camera.azimuth(-1.0f);
		light.setPosition(camera.getPosition());
		break;
	case GLUT_KEY_RIGHT:		// rotate cubes right around Y-axis
		camera.azimuth(1.0f);
		light.setPosition(camera.getPosition());
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
	window_width = w;
	window_height = h;

	// Change the aspect ratio if the window is reshaped
	glViewport( 0, 0, w, h );
	camera.updateAspect((GLfloat(w))/h);

	// Set redisplay flag
	glutPostRedisplay();
}

void idleCallback()
{
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
}
