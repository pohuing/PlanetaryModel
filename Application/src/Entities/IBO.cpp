#include "IBO.h"
#include <utility>

IndexBufferObject::IndexBufferObject() {
	m_VerticesCount = 0;
	m_IBO = 0;
	glGenBuffers(1, &m_IBO);
}

IndexBufferObject::~IndexBufferObject() {
	glDeleteBuffers(1, &m_IBO);
}

void IndexBufferObject::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
}

void IndexBufferObject::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBufferObject::BufferData(const GLenum target, const GLsizei size, const GLvoid* data, const GLenum usage) {
	glBufferData(target, size, data, usage);
	m_VerticesCount = size / sizeof(unsigned int);
}

GLsizei IndexBufferObject::GetIndicesCount() const
{
	return m_VerticesCount;
}

IndexBufferObject::IndexBufferObject ( IndexBufferObject&& other ) noexcept {
	std::swap ( m_IBO, other.m_IBO );
	std::swap(m_VerticesCount, other.m_VerticesCount);
}

IndexBufferObject& IndexBufferObject::operator= ( IndexBufferObject&& other ) noexcept {
	std::swap ( m_IBO, other.m_IBO );
	std::swap(m_VerticesCount, other.m_VerticesCount);
	return *this;
}
