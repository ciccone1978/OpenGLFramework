#pragma once
#include <GL/glew.h>
#include <vector>

struct VertexAttribute
{
	GLint size;
	GLenum type;
	GLboolean normalized;
};

class CVertexArray
{
public:
	CVertexArray();
	~CVertexArray();

	void bind() const;
	void unbind() const;
	void addVertexAttribute(const VertexAttribute& va);
	void enableBuffer();

private:
	GLuint mId;
	std::vector<VertexAttribute> mVertAttrib;
	unsigned int mStride;
};

