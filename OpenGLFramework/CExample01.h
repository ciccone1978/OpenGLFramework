#pragma once
#include "CWindow.h"
#include "CShader.h"
#include "CVertexArray.h"
#include "CVertexBuffer.h"
#include "GLSLsource.h"
#include "CStaticGeometry.h"
#include "CCamera.h"

class CExample01 : public CWindow
{
public:
	CExample01();
	~CExample01();

	void init() override;
	void render() override;
	void update() override;
	void handleInput() override;

private:
	CShader* _shader1 = nullptr;
	CShader* _shader2 = nullptr;
	CVertexArray* _vao1 = nullptr;
	CVertexArray* _vao2 = nullptr;

	CCamera* _camera = nullptr;

	glm::mat4 model = glm::mat4(1.0f);
	//glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 mvp = glm::mat4(1.0f);
};

