#include <iostream>
#include "CWindow.h"

CWindow::CWindow()
{
}

CWindow::~CWindow()
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}

bool CWindow::createWindow(const std::string& title, const unsigned int w, const unsigned int h)
{
	//initialize GLFW
	if (!glfwInit())
	{
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window and context
	_window = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
	if (!_window)
	{
		glfwTerminate();
		return false;
	}

	//make current context
	glfwMakeContextCurrent(_window);

	//GLEW init
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}

	_screen_width = w;
	_screen_height = h;
	
	return true;
}

void CWindow::runApp()
{
	init();

	_lastFrameTime = glfwGetTime();

	while (!glfwWindowShouldClose(_window))
	{
		float currentTime = glfwGetTime();
		_timeDelta = currentTime - _lastFrameTime;
		_lastFrameTime = currentTime;

		handleInput();
		render();
		update();

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
}

void CWindow::closeWindow()
{
	glfwSetWindowShouldClose(_window, true);
}

std::string CWindow::getVersion()
{
	/*
	std::cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	*/
	return std::string();
}

bool CWindow::keyPressed(int keyCode) const
{
	return glfwGetKey(_window, keyCode) == GLFW_PRESS;
}
