#include "CExample01.h"

glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
ImVec4 objectColor = ImVec4(1.0f, 0.5f, 0.31f, 1.00f);
ImVec4 lightColor = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

CExample01::CExample01()
{
}

CExample01::~CExample01()
{
	delete _vao1;
	delete _vao2;
	delete _shader1;
	delete _shader2;
	delete _camera;
}

void CExample01::init()
{
	VertexAttribute vaPosition = {3, GL_FLOAT, GL_FALSE};
	VertexAttribute vaNormal = { 3, GL_FLOAT, GL_FALSE };
	CVertexBuffer vbo(CStaticGeometry::cube_normal, sizeof(CStaticGeometry::cube_normal));

	_vao1 = new CVertexArray();
	_vao1->addVertexAttribute(vaPosition);
	_vao1->addVertexAttribute(vaNormal);
	_vao1->enableBuffer();
	_vao1->unbind();

	_vao2 = new CVertexArray();
	_vao2->addVertexAttribute(vaPosition);
	_vao2->addVertexAttribute(vaNormal);
	_vao2->enableBuffer();
	_vao2->unbind();
	
	_shader1 = new CShader();
	_shader1->loadFromText(GL_VERTEX_SHADER, vertexShaderSource);
	_shader1->loadFromText(GL_FRAGMENT_SHADER, cubeFragmentShaderSource);
	//_shader1->loadFromFile(GL_VERTEX_SHADER, "shader\\vsExample01.glsl");
	//_shader1->loadFromFile(GL_FRAGMENT_SHADER, "shader\\fsExample01_1.glsl");
	_shader1->link();
	_shader1->registerUniformLocation("model");
	_shader1->registerUniformLocation("view");
	_shader1->registerUniformLocation("projection");
	_shader1->registerUniformLocation("objectColor");
	_shader1->registerUniformLocation("lightColor");
	_shader1->registerUniformLocation("lightPos");
	_shader1->registerUniformLocation("viewPos");

	//light source shader
	_shader2 = new CShader();
	_shader2->loadFromText(GL_VERTEX_SHADER, vertexShaderSource);
	_shader2->loadFromText(GL_FRAGMENT_SHADER, lightFragmentShaderSource);
	//_shader2->loadFromFile(GL_VERTEX_SHADER, "shader\\vsExample01.glsl");
	//_shader2->loadFromFile(GL_FRAGMENT_SHADER, "shader\\fsExample01_2.glsl");
	_shader2->link();
	_shader2->registerUniformLocation("model");
	_shader2->registerUniformLocation("view");
	_shader2->registerUniformLocation("projection");
	_shader2->registerUniformLocation("lightColor");

	_camera = new CCamera(glm::vec3(-4.8f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	projection = glm::perspective(glm::radians(45.0f), (float)getScreenWidth() / (float)getScreenHeight(), 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);
}

void CExample01::render()
{
	glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	model = glm::mat4(1.0f);
	//mvp = projection * _camera->getViewMatrix() * model;

	_shader1->bind();
	_shader1->setUniform("model", model);
	_shader1->setUniform("view", _camera->getViewMatrix());
	_shader1->setUniform("projection", projection);
	_shader1->setUniform("objectColor", objectColor.x, objectColor.y, objectColor.z);
	_shader1->setUniform("lightColor", lightColor.x, lightColor.y, lightColor.z);
	_shader1->setUniform("lightPos", lightPos);
	_shader1->setUniform("viewPos", _camera->getPosition());
	
	_vao1->bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//light source
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));
	//mvp = projection * _camera->getViewMatrix() * model;

	_shader2->bind();
	_shader2->setUniform("model", model);
	_shader2->setUniform("view", _camera->getViewMatrix());
	_shader2->setUniform("projection", projection);
	_shader2->setUniform("lightColor", lightColor.x, lightColor.y, lightColor.z);

	_vao2->bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
}

void CExample01::renderImGui()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	{
		ImGui::Begin("Hello, world!");
		ImGui::Text("WASD walk around");

		ImGui::ColorEdit3("Object color", (float*)&objectColor);
		ImGui::ColorEdit3("Light color", (float*)&lightColor);
		ImGui::ColorEdit3("Clear color", (float*)&clearColor);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	ImGui::Render();
	//int display_w, display_h;
	//glfwGetFramebufferSize(window, &display_w, &display_h);
	//glViewport(0, 0, display_w, display_h);
	
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void CExample01::update()
{
}

void CExample01::handleInput()
{
	if (keyPressed(GLFW_KEY_ESCAPE))
		closeWindow();

	if (keyPressed(GLFW_KEY_W))
	{
		_camera->move(10.0f * getTimeDelta());
	}
	if (keyPressed(GLFW_KEY_S))
		_camera->move(-10.0f * getTimeDelta());

	if (keyPressed(GLFW_KEY_A))
		_camera->rotate(135.0f * getTimeDelta());

	if (keyPressed(GLFW_KEY_D))
		_camera->rotate(-135.0f * getTimeDelta());
}
