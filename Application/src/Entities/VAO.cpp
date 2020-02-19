#include "VAO.h"

VertexArrayObject::VertexArrayObject() {
	glGenVertexArrays(1, &m_VAO);
}

VertexArrayObject::~VertexArrayObject() {
	glDeleteVertexArrays(1, &m_VAO);
}

VertexArrayObject::VertexArrayObject ( VertexArrayObject&& other ) noexcept {
	std::swap ( m_VAO, other.m_VAO );
}

void VertexArrayObject::Bind() {
	glBindVertexArray(m_VAO);
}

void VertexArrayObject::Unbind() {
	glBindVertexArray(0);
}

void VertexArrayObject::SetupAttribPointers() {
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_Position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (const void*)offsetof(Vertex, m_Normal));
}

VertexArrayObject& VertexArrayObject::operator= ( VertexArrayObject&& other ) noexcept {
	std::swap ( m_VAO, other.m_VAO );
	return *this;
}
