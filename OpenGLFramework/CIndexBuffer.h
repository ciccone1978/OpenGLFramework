#pragma once
#include <GL/glew.h>

class CIndexBuffer
{
public:
	CIndexBuffer(void* data, unsigned int size);
	~CIndexBuffer();

	void bind() const;
	void unbind() const;

private:
	GLuint mId;
};


