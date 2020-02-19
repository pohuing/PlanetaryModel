#include "IBO.h"
#include <utility>

IndexBufferObject::IndexBufferObject() {
	m_VerticesCount = 0;
	glGenBuffers(1, &m_IBO);
}

IndexBufferObject::~IndexBufferObject() {
	glDeleteBuffers(1, &m_IBO);
}

void IndexBufferObject::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
}

void IndexBufferObject::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBufferObject::BufferData(GLenum target, GLsizei size, const GLvoid* data, GLenum usage) {
	glBufferData(target, size, data, usage);
	m_VerticesCount = size / sizeof(unsigned int);
}

GLsizei IndexBufferObject::GetIndicesCount() {
	return m_VerticesCount;
}

IndexBufferObject::IndexBufferObject ( IndexBufferObject&& other ) {
	std::swap ( m_IBO, other.m_IBO );
}

IndexBufferObject& IndexBufferObject::operator= ( IndexBufferObject&& other ) {
	std::swap ( m_IBO, other.m_IBO );
	return *this;
}
