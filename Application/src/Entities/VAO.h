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
	GLuint m_VAO;
};