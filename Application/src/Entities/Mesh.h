#pragma once
#include <vector>
#include "VAO.h"
#include "VBO.h"
#include "IBO.h"
#include "STBImage.h"
#include "Texture.h"
#include "Vertex.h"
#include "../Rendering/Shaderprogram.h"

class Mesh {
public:
	Mesh() = default;
	Mesh(const Mesh& other) = delete;
	Mesh(Mesh&& other) = default;
	Mesh& operator=(Mesh&& other) = default;
	Mesh& operator=(const Mesh& other) = delete;
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, STBImage texture);
	~Mesh() = default;
	void Load();
	void Unload();
	void Draw();

	int GetTextureLocation() const;
	
private:
	void Bind();
	void Unbind();
	
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	STBImage m_imageData;
	
	VertexArrayObject m_VAO;
	VertexBufferObject m_VBO;
	IndexBufferObject m_IBO;
	Texture m_texture;
	bool m_loaded = false;
};
