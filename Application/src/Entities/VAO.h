#pragma once
#include <GLEW/glew.h>
#include "Vertex.h"

class VertexArrayObject {
public:
	VertexArrayObject();
	~VertexArrayObject();
	void Bind();
	void Unbind();
	void SetupAttribPointers();
private:
	//VertexArrayObject(const VertexArrayObject& other);
	GLuint m_VAO;
};