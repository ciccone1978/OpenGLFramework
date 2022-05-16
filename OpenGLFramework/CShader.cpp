#include "CShader.h"

CShader::CShader()
{
	mId = 0;
	mShaderObj.clear();
	mUniformLoc.clear();
}

CShader::~CShader()
{
	glDeleteProgram(mId);
}

void CShader::loadFromText(GLenum shaderType, const char* shaderSource)
{
	//const char* source = shaderSource.c_str();

	GLuint shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &shaderSource, nullptr);
	glCompileShader(shaderId);

	//check compiler errors
	GLint success;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char log[512];
		glGetShaderInfoLog(shaderId, sizeof(log), nullptr, log);
		std::cout << "ERROR: GL_COMPILE_STATUS " << log << std::endl;
	}

	//store shader object
	//mShaderObj.insert(shaderType, shaderId);
	mShaderObj[shaderType] = shaderId;
}

void CShader::loadFromFile(GLenum shaderType, const char* shaderSource)
{
	std::ifstream sourceFile(shaderSource);
	if (sourceFile.is_open())
	{
		std::stringstream buffer;
		buffer << sourceFile.rdbuf();
		sourceFile.close();

		loadFromText(shaderType, buffer.str().c_str());
	}
	else
	{
		std::cout << "ERROR: CAN'T OPEN FILE " << shaderSource << std::endl;
	}
}

void CShader::link()
{
	mId = glCreateProgram();

	//attach shader objects
	for (auto it = mShaderObj.begin(); it != mShaderObj.end(); ++it)
		glAttachShader(mId, it->second);
	
	glLinkProgram(mId);

	//check linker errors
	GLint success;
	glGetProgramiv(mId, GL_LINK_STATUS, &success);
	if (!success)
	{
		char log[512];
		glGetProgramInfoLog(mId, sizeof(log), nullptr, log);
		std::cout << "ERROR: GL_LINK_STATUS " << log << std::endl;
 	}

	glValidateProgram(mId);

	//delete shader obj
	for (auto it = mShaderObj.begin(); it != mShaderObj.end(); ++it)
		glDeleteShader(it->second);
}

GLuint CShader::getShaderId() const
{
	return mId;
}

void CShader::registerUniformLocation(const char* uniformName)
{
	GLuint u = glGetUniformLocation(mId, uniformName);
	mUniformLoc[uniformName] = u;
}

GLuint CShader::getUniformLocation(const char* uniformName)
{
	return mUniformLoc[uniformName];
}

void CShader::setUniform(const char* uniformName, float v0, float v1, float v2)
{

	glUniform3f(mUniformLoc[uniformName], v0, v1, v2);
}

void CShader::setUniform(const char* uniformName, const glm::vec3& v)
{
	glUniform3fv(mUniformLoc[uniformName], 1, &v[0]);
}

void CShader::setUniform(const char* uniformName, const glm::mat4& m)
{
	glUniformMatrix4fv(mUniformLoc[uniformName], 1, GL_FALSE, glm::value_ptr(m));
}

void CShader::bind() const
{
	glUseProgram(mId);
}

void CShader::unbind() const
{
	glUseProgram(0);
}

