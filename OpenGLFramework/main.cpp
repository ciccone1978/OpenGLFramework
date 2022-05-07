//
//	OpenGL
// 

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif // !GLEW_STATIC

#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <STB/stb_image.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "CShader.h"
#include "CVertexArray.h"
#include "CVertexBuffer.h"
#include "GLSLsource.h"

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

//the cube
float vxCube[] = {
	//position			
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f
};

int main(void)
{
	//initialize GLFW
	if (!glfwInit())
	{
		std::cout << "Error: glfwInit()" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window and context
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Cube", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Error: glfwCreateWindow()" << std::endl;
		glfwTerminate();
		return -1;
	}

	//make current context
	glfwMakeContextCurrent(window);

	//GLEW init
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error: glewInit()" << std::endl;
		glfwTerminate();
		return -1;
	}

	//OpenGL version info
	std::cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	VertexAttribute vaPosition = { 3, GL_FLOAT, GL_FALSE };
	CVertexBuffer vbo(vxCube, sizeof(vxCube));

	//cube
	CVertexArray cubeVao;
	cubeVao.addVertexAttribute(vaPosition);
	cubeVao.enableBuffer();
	//cubeVao.unbind();

	//light source
	CVertexArray lightSourceVao;
	lightSourceVao.addVertexAttribute(vaPosition);
	lightSourceVao.enableBuffer();
	//lightSourceVao.unbind();

	//cube shader
	CShader cubeShader;
	cubeShader.loadFromText(GL_VERTEX_SHADER, vertexShaderSource);
	cubeShader.loadFromText(GL_FRAGMENT_SHADER, cubeFragmentShaderSource);
	cubeShader.link();
	cubeShader.registerUniformLocation("mvp");
	cubeShader.registerUniformLocation("cubeColor");
	cubeShader.registerUniformLocation("lightSourceColor");

	//light source shader
	CShader lightSourceShader;
	lightSourceShader.loadFromText(GL_VERTEX_SHADER, vertexShaderSource);
	lightSourceShader.loadFromText(GL_FRAGMENT_SHADER, lightFragmentShaderSource);
	lightSourceShader.link();
	lightSourceShader.registerUniformLocation("mvp");

	//enable z-buffer testing
	glEnable(GL_DEPTH_TEST);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 mvp = glm::mat4(1.0f);
	
	view = glm::lookAt(glm::vec3(6.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

	//loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//
		//cube rendering
		//
		model = glm::mat4(1.0f);
		mvp = projection * view * model;

		cubeShader.bind();
		glUniformMatrix4fv(cubeShader.getUniformLocation("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
		glUniform4f(cubeShader.getUniformLocation("cubeColor"), 1.0f, 0.5f, 0.31f, 1.04f);
		glUniform4f(cubeShader.getUniformLocation("lightSourceColor"), 1.0f, 1.0f, 1.0f, 1.0f);
		cubeVao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//
		//light source rendering
		//
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.2f, 1.0f, 2.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		mvp = projection * view * model;

		lightSourceShader.bind();
		glUniformMatrix4fv(lightSourceShader.getUniformLocation("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
		lightSourceVao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//destroy window
	glfwDestroyWindow(window);

	//terminate GLFW
	glfwTerminate();

	return 0;
}

