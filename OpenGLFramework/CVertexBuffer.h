#pragma once
#include <GL/glew.h>

class CVertexBuffer
{
public:
	CVertexBuffer(void* data, unsigned int size);
	~CVertexBuffer();

	void bind() const;
	void unbind() const;

private:
	GLuint mId;
};

