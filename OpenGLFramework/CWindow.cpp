#include <iostream>
#include "CWindow.h"

CWindow::CWindow()
{
}

CWindow::~CWindow()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

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

	const char* glsl_version = "#version 330";
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
	glfwSwapInterval(1);

	//GLEW init
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}

	//Setup ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

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
		
		glfwPollEvents();

		handleInput();
		render();
		renderImGui();
		update();

		glfwSwapBuffers(_window);
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
