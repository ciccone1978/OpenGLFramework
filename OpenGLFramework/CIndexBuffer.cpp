#include "CIndexBuffer.h"

CIndexBuffer::CIndexBuffer(void* data, unsigned int size) : mId(0)
{
	glGenBuffers(1, &mId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

CIndexBuffer::~CIndexBuffer()
{
	glDeleteBuffers(1, &mId);
}

void CIndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
}

void CIndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
