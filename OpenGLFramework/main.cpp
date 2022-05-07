//
//	OpenGLTutorial - Hello Cube
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
float vertices[] = {
	//position			  //texture	
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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

	//VAO - Vertex array object
	//unsigned int vao;
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);

	CVertexArray vao;
	CVertexBuffer vbo(vertices, sizeof(vertices));

	//create texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//texture option
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//load imgage
	int width, height, nChannels;
	unsigned char* image = stbi_load("container.jpg", &width, &height, &nChannels, 0);
	if (image)
	{
		//associate to the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Error loading texture" << std::endl;
	}
	stbi_image_free(image);

	//Shader Program compile & link
	CShader shaderProgram;
	shaderProgram.loadFromText(GL_VERTEX_SHADER, vsSource);
	shaderProgram.loadFromText(GL_FRAGMENT_SHADER, fsSource);
	shaderProgram.link();
	shaderProgram.registerUniformLocation("mvp");
	shaderProgram.bind();

	//set vertex attributes
	unsigned int posLocation = 0;
	glEnableVertexAttribArray(posLocation);
	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

	unsigned int texLocation = 1;
	glEnableVertexAttribArray(texLocation);
	glVertexAttribPointer(texLocation, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	

	//enable z-buffer testing
	glEnable(GL_DEPTH_TEST);

	//loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//MVP
		glm::mat4 mModel = glm::mat4(1.0f);
		glm::mat4 mView = glm::mat4(1.0f);
		glm::mat4 mProject = glm::mat4(1.0f);

		//model
		mModel = glm::rotate(mModel, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		mModel = glm::scale(mModel, glm::vec3(0.5f, 0.5f, 0.5f));
		//view
		mView = glm::translate(mView, glm::vec3(0.0f, 0.0f, -3.0f));
		//projection
		mProject = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

		glm::mat4 mMVP = mProject * mView * mModel;
		glUniformMatrix4fv(shaderProgram.getUniformLocation("mvp"), 1, GL_FALSE, glm::value_ptr(mMVP));

		//vao.bind();
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

