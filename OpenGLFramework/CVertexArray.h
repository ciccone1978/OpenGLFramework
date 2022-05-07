#pragma once
#include <GL/glew.h>

class CVertexArray
{
public:
	CVertexArray();
	~CVertexArray();

	void bind() const;
	void unbind() const;
	void addBuffer();

private:
	GLuint mId;
};

