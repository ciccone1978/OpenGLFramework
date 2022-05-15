#pragma once
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif // !GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <string>

class CWindow
{
public:
	CWindow();
	~CWindow();

	bool createWindow(const std::string& title, const unsigned int w, const unsigned int h);
	void runApp();
	void closeWindow();
	bool keyPressed(int keyCode) const;
	std::string getVersion();

	virtual void init() {};
	virtual void render() {};
	virtual void update() {};
	virtual void handleInput() {}

	unsigned int getScreenWidth() const { return _screen_width; }
	unsigned int getScreenHeight() const { return _screen_height; }
	float getTimeDelta() const { return _timeDelta; }

private:
	GLFWwindow* _window = nullptr;
	unsigned int _screen_width = 0;
	unsigned int _screen_height = 0;
	float _lastFrameTime = 0.0f;
	float _timeDelta = 0.0f;
};

