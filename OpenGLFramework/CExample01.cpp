#include "CExample01.h"

glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

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
	_shader2->link();
	_shader2->registerUniformLocation("model");
	_shader2->registerUniformLocation("view");
	_shader2->registerUniformLocation("projection");

	_camera = new CCamera(glm::vec3(-4.8f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	projection = glm::perspective(glm::radians(45.0f), (float)getScreenWidth() / (float)getScreenHeight(), 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void CExample01::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	model = glm::mat4(1.0f);
	//mvp = projection * _camera->getViewMatrix() * model;

	_shader1->bind();
	glUniformMatrix4fv(_shader1->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(_shader1->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(_camera->getViewMatrix()));
	glUniformMatrix4fv(_shader1->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniform3f(_shader1->getUniformLocation("objectColor"), 1.0f, 0.5f, 0.31f);
	glUniform3f(_shader1->getUniformLocation("lightColor"), 1.0f, 1.0f, 1.0f);
	glUniform3fv(_shader1->getUniformLocation("lightPos"), 1, &lightPos[0]);
	glm::vec3 viewPos = _camera->getPosition();
	glUniform3fv(_shader1->getUniformLocation("viewPos"), 1, &viewPos[0]);
	_vao1->bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//light source
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));
	//mvp = projection * _camera->getViewMatrix() * model;

	_shader2->bind();
	glUniformMatrix4fv(_shader2->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(_shader2->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(_camera->getViewMatrix()));
	glUniformMatrix4fv(_shader2->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
	_vao2->bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
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
