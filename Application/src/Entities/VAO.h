#pragma once
#include <GLEW/glew.h>
#include "Vertex.h"

class VertexArrayObject {
public:
	VertexArrayObject();
	~VertexArrayObject();
	VertexArrayObject(const VertexArrayObject&) = delete;
	VertexArrayObject(VertexArrayObject &&other);
	VertexArrayObject& operator=(VertexArrayObject&& other);
	void Bind();
	void Unbind();
	void SetupAttribPointers();
private:
	//VertexArrayObject(const VertexArrayObject& other);
	GLuint m_VAO;
};
