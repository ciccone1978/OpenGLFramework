#include "CVertexArray.h"

CVertexArray::CVertexArray()
	:mId(0)
{
	glGenVertexArrays(1, &mId);
	glBindVertexArray(mId);
}

CVertexArray::~CVertexArray()
{
	glDeleteVertexArrays(1, &mId);
}

void CVertexArray::bind() const
{
	glBindVertexArray(mId);
}

void CVertexArray::unbind() const
{
	glBindVertexArray(0);
}

void CVertexArray::addBuffer()
{
	//for(){}
	//glVertexAttribPointer(...)
	//glEnableVertexAttribArray()
}
