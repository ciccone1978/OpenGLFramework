#include "CVertexArray.h"

CVertexArray::CVertexArray()
	:mId(0), mStride(0)
{
	mVertAttrib.clear();

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

void CVertexArray::addVertexAttribute(const VertexAttribute& va)
{
	mVertAttrib.push_back(va);
	mStride += va.size;
}

void CVertexArray::enableBuffer()
{
	unsigned int offset = 0;
	for (unsigned int i = 0; i < mVertAttrib.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, mVertAttrib[i].size, mVertAttrib[i].type, mVertAttrib[i].normalized, mStride * sizeof(float), (void*)(offset*sizeof(float)));
		offset += mVertAttrib[i].size;
	}
}
