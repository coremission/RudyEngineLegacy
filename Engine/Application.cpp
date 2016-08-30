﻿#include "Application.h"
#include "Model/Scene.h"

#include <iostream>
#include <freeglut/freeglut.h>
#include <glew/glew.h>
#include <memory>

using namespace std;

// static field initialization
shared_ptr<Models::Scene> Application::_scene;

void Application::initialize(int* argc, char ** argv) {
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("OpenGL First Window");
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glutKeyboardFunc(processInput);
	glewInit();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (glewIsSupported("GL_VERSION_4_3"))
	{
		std::cout << " GLEW Version is 4.3\n ";
	}
	else
	{
		std::cout << "GLEW 4.3 not supported\n ";
	}

	glutDisplayFunc(renderScene);
}

void Application::setUpScene(shared_ptr<Models::Scene> scene) {
	Application::_scene = scene;
}

void Application::runMainLoop()
{
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutMainLoop();
}

void Application::renderScene() {
	static float time = 0.0f;
	time += 0.0001f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//
	for(auto it = _scene->begin(); it != _scene->end(); ++it)
	{
		drawGameObject(*it->second, time);
	}
	
	glutSwapBuffers();
	glutPostRedisplay();
}

void Application::drawGameObject(GameObject& gameObject, float time)
{
	gameObject.transform.setLocalYawPitchRoll(glm::vec3(0, time, 0));
	gameObject.transform.setLocalPosition(glm::vec3(0, time, 0));
	gameObject.renderer->render();
}

void Application::processInput(unsigned char key, int x, int y)
{
	std::cout << key;

	if (key == 27) // ESCAPE
		exit();
}

void Application::exit()
{
	glutLeaveMainLoop();
}