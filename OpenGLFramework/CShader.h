#pragma once
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

class CShader
{
public:
	CShader();
	~CShader();

	void loadFromText(GLenum shaderType, const char* shaderSource);
	void loadFromFile(GLenum shaderType, const char* shaderSource);
	void link();
	void bind() const;
	void unbind() const;
	GLuint getShaderId() const;
	void registerUniformLocation(const char* uniformName);
	GLuint getUniformLocation(const char* uniformName);

	void setUniform(const char* uniformName, float v0, float v1, float v2);
	void setUniform(const char* uniformName, const glm::vec3& v);
	void setUniform(const char* uniformName, const glm::mat4& m);

private:
	GLuint mId;
	std::map<GLenum, GLuint> mShaderObj;
	std::map<std::string, GLuint> mUniformLoc;
};

