#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) :
	m_vertices(std::move(vertices)), m_indices(std::move(indices)) {
	m_loaded = false;
	Load();
}

void Mesh::Load() {
	if(m_loaded)
		return;

	m_VAO.Bind();

	m_VBO.Bind();
	m_VBO.BufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);
	m_VAO.SetupAttribPointers();
	m_VBO.Unbind();

	m_IBO.Bind();
	m_IBO.BufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);
	m_IBO.Unbind();

	m_VAO.Unbind();
	m_loaded = true;
}

void Mesh::Unload() {
	m_VAO = VertexArrayObject();
	m_VBO = VertexBufferObject();
	m_IBO = IndexBufferObject();
	m_loaded = false;
}

Mesh::Mesh() {}

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
