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
float vxCube[] = {
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

float vxTriangle[] = {
	//position         //color    
	0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
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
	VertexAttribute vaColor = { 3, GL_FLOAT, GL_FALSE };
	VertexAttribute vaTexture = { 2, GL_FLOAT, GL_FALSE };

	CVertexArray vao1;
	CVertexBuffer vbo1(vxCube, sizeof(vxCube));
	vao1.addVertexAttribute(vaPosition);
	vao1.addVertexAttribute(vaTexture);
	vao1.enableBuffer();
	vao1.unbind();

	CVertexArray vao2;
	CVertexBuffer vbo2(vxTriangle, sizeof(vxTriangle));
	vao2.addVertexAttribute(vaPosition);
	vao2.addVertexAttribute(vaColor);
	vao2.enableBuffer();
	vao2.unbind();

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

	//CUBE: Shader Program compile & link
	CShader shaderProgram1;
	shaderProgram1.loadFromText(GL_VERTEX_SHADER, vsSource);
	shaderProgram1.loadFromText(GL_FRAGMENT_SHADER, fsSource);
	shaderProgram1.link();
	shaderProgram1.registerUniformLocation("mvp");
	//shaderProgram1.bind();

	//TRIANGLE: Shader Program compile & link
	CShader shaderProgram2;
	shaderProgram2.loadFromText(GL_VERTEX_SHADER, vs01);
	shaderProgram2.loadFromText(GL_FRAGMENT_SHADER, fs01);
	shaderProgram2.link();
	shaderProgram2.registerUniformLocation("transform");
	//shaderProgram2.bind();

	//enable z-buffer testing
	glEnable(GL_DEPTH_TEST);

	//loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//
		//draw the CUBE
		//
		shaderProgram1.bind();
		vao1.bind();

		//MVP
		glm::mat4 mModel = glm::mat4(1.0f);
		glm::mat4 mView = glm::mat4(1.0f);
		glm::mat4 mProject = glm::mat4(1.0f);

		//model
		mModel = glm::translate(mModel, glm::vec3(0.5f, 0.5f, 0.5f));
		mModel = glm::rotate(mModel, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		mModel = glm::scale(mModel, glm::vec3(0.5f, 0.5f, 0.5f));
		//view
		mView = glm::translate(mView, glm::vec3(0.0f, 0.0f, -3.0f));
		//projection
		mProject = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

		glm::mat4 mMVP = mProject * mView * mModel;
		glUniformMatrix4fv(shaderProgram1.getUniformLocation("mvp"), 1, GL_FALSE, glm::value_ptr(mMVP));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//
		//draw the TRIANGLE
		//
		shaderProgram2.bind();
		vao2.bind();

		glm::mat4 mTrans = glm::mat4(1.0f);
		//mTrans = glm::translate(mTrans, glm::vec3(0.5f, -0.5f, 0.0f)); //translate
		mTrans = glm::rotate(mTrans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f)); //rotate
		//mTrans = glm::scale(mTrans, glm::vec3(0.5f, 0.5f, 0.5f)); //scale
		glUniformMatrix4fv(shaderProgram2.getUniformLocation("transform"), 1, GL_FALSE, glm::value_ptr(mTrans));
		
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//destroy window
	glfwDestroyWindow(window);

	//terminate GLFW
	glfwTerminate();

	return 0;
}

