#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, STBImage texture) :
	m_vertices(std::move(vertices)), m_indices(std::move(indices)), m_imageData(std::move(texture)) {
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

	m_texture.Bind();
	m_texture.BufferData(m_imageData.GetWidth(), m_imageData.GetHeight(), m_imageData.GetData());
	m_texture.Unbind();
	
	m_VAO.Unbind();
	m_loaded = true;
}

void Mesh::Unload() {
	m_VAO = VertexArrayObject();
	m_VBO = VertexBufferObject();
	m_IBO = IndexBufferObject();
	m_texture = Texture();
	m_loaded = false;
}

void Mesh::Draw() {
	Bind();
	glDrawElements(GL_TRIANGLES, m_IBO.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
	Unbind();
}

int Mesh::GetTextureLocation() const
{
	return m_texture.GetID();
}

void Mesh::Bind() {
	m_VAO.Bind();
	m_VBO.Bind();
	m_IBO.Bind();
	m_texture.Bind();
}

void Mesh::Unbind() {
	m_VAO.Unbind();
	m_VBO.Unbind();
	m_IBO.Unbind();
	m_texture.Unbind();
}
