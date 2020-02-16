#pragma once
#include <vector>
#include <GLM/glm.hpp>
#include "VAO.h"
#include "VBO.h"
#include "IBO.h"
#include "Vertex.h"

class Mesh {
public:
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	void Draw();

	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;

private:
	void Bind();
	void Unbind();
	VertexArrayObject m_VAO;
	VertexBufferObject m_VBO;
	IndexBufferObject m_IBO;
};


