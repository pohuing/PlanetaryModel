#pragma once
#include <GLEW/glew.h>
#include "Vertex.h"

class VertexArrayObject {
public:
	VertexArrayObject();
	~VertexArrayObject();
	VertexArrayObject(const VertexArrayObject&) = delete;
	VertexArrayObject(VertexArrayObject &&other) noexcept;
	VertexArrayObject& operator=(VertexArrayObject&& other) noexcept;
	void Bind();
	void Unbind();
	void SetupAttribPointers();
private:
	//VertexArrayObject(const VertexArrayObject& other);
	GLuint m_VAO = 0;
};
