#include "CVertexBuffer.h"

CVertexBuffer::CVertexBuffer(void* data, unsigned int size)	: mId(0)
{
	glGenBuffers(1, &mId);
	glBindBuffer(GL_ARRAY_BUFFER, mId);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

CVertexBuffer::~CVertexBuffer()
{
	glDeleteBuffers(1, &mId);
}

void CVertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, mId);
}

void CVertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
