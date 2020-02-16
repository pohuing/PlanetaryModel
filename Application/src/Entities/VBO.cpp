#include "VBO.h"

VertexBufferObject::VertexBufferObject()
{
	glGenBuffers(1, &m_VBO);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &m_VBO);
}

void VertexBufferObject::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
}

void VertexBufferObject::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::BufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
{
	glBufferData(target, size, data, usage);
}

