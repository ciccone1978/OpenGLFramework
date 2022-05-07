#include <GL/glew.h>
#include <iostream>
#include <map>

class CShader
{
public:
	CShader();
	~CShader();

	void loadFromText(GLenum shaderType, const char* shaderSource);
	void link();
	void bind() const;
	void unbind() const;
	GLuint getShaderId() const;
	void registerUniformLocation(const char* uniformName);
	GLuint getUniformLocation(const char* uniformName);

private:
	GLuint mId;
	std::map<GLenum, GLuint> mShaderObj;
	std::map<std::string, GLuint> mUniformLoc;
};

