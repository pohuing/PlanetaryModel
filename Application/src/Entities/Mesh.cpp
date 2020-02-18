#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) :
	m_vertices(vertices), m_indices(indices) {
	m_VAO.Bind();

	m_VBO.Bind();
	m_VBO.BufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	m_VAO.SetupAttribPointers();
	m_VBO.Unbind();

	m_IBO.Bind();
	m_IBO.BufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	m_IBO.Unbind();

	m_VAO.Unbind();
}

Mesh::Mesh() {
}

void Mesh::Draw() {
	Bind();
	glDrawElements(GL_TRIANGLES, m_IBO.GetIndicesCount(), GL_UNSIGNED_INT, (GLvoid*)0);
	Unbind();
}

void Mesh::Bind() {
	m_VAO.Bind();
	m_VBO.Bind();
	m_IBO.Bind();
}

void Mesh::Unbind() {
	m_VAO.Unbind();
	m_VBO.Unbind();
	m_IBO.Unbind();
}