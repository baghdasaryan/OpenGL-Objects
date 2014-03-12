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
	rectangles[0] = new ObjectRectangle(1.0f, vec3(0.0f, 1.5f, 3.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), 0.2f, 0.6f, 0.2f, 100.0f, &camera, &light);
	rectangles[0]->init("");

	// Set OpenGL parameters
	glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

// Draw the scene
void drawScene()
{
	// Draw the objects
	rectangles[0]->draw(edgesOn, meshOn);		// bool => edges, number => mesh
}

// Clean up
void cleanUp()
{
	delete rectangles[0];
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
	case 'q':				// Exit on 'q'
	case 'Q':				// Exit on 'Q'
		cleanUp();
		exit(0);
		break;
	case 32:				// reset default positioning on Space
		break;

	case 'e':				// switch between drawing edges on 'e'
	case 'E':				// switch between drawing edges on 'E'
		edgesOn = !edgesOn;
		break;

	case 'm':				// switch between drawing the mesh and filling the object on 'm'
	case 'M':				// switch between drawing the mesh and filling the object on 'M'
		meshOn = !meshOn;
		break;

	case 'w':				// move camera up on 'w'
	case 'W':				// move camera up on 'W'
		camera.vertical(0.1f);
		light.setPosition(camera.getPosition());
		break;
	case 's':				// move camera down on 's'
	case 'S':				// move camera down on 'S'
		camera.vertical(-0.1f);
		light.setPosition(camera.getPosition());
		break;
	case 'a':				// move camera left on 'a'
	case 'A':				// move camera left on 'A'
		camera.horizontal(-0.1f);
		light.setPosition(camera.getPosition());
		break;
	case 'd':				// move camera right on 'd'
	case 'D':				// move camera right on 'D'
		camera.horizontal(0.1f);
		light.setPosition(camera.getPosition());
		break;

	case '8':				// look up on '8'
		camera.pitch(-0.03);
		break;
	case '2':				// look down on '2'
		camera.pitch(0.03f);
		break;
	case '4':				// look left on '4'
		camera.yaw(0.05f);
		break;
	case '6':				// look right on '6'
		camera.yaw(-0.05f);
		break;
	case '1':				// rotate camera left on '1'
		camera.roll(3.5f);
		break;
	case '3':				// rotate camera right on '3'
		camera.roll(-3.5f);
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
		camera.altitude(0.8);
		light.setPosition(camera.getPosition());
		break;
	case GLUT_KEY_DOWN:			// positive rotation around X-axis
		camera.altitude(-0.8);
		light.setPosition(camera.getPosition());
		break;
	case GLUT_KEY_LEFT:			// rotate cubes left around Y-axis
		camera.azimuth(-1.5f);
		light.setPosition(camera.getPosition());
		break;
	case GLUT_KEY_RIGHT:		// rotate cubes right around Y-axis
		camera.azimuth(1.5f);
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
