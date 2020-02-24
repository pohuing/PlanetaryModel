#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "../Entities/Vertex.h"
#include <GLM/glm.hpp>

namespace 
{	
	typedef glm::vec3 VertexCoordinate;
	typedef glm::vec3 VertexNormal;
	typedef glm::vec3 TextureCoordinate;
}

class Parser {
public:
	Parser(std::string path);
	void ReadFile();
	std::vector<Vertex> GetVertices() const;
	std::vector<unsigned int> GetIndices() const;
private:
	void Parse(std::stringstream& code);
	void ParseLine(const std::vector<std::string>& words);
	void ParseGeometricVertex(const std::vector<std::string>& coordinates);
	void ParseVertexNormals(const std::vector<std::string>& normals);
	void ParseTextureCoordinate(const std::vector<std::string>& coordinates);
	void ParseFace(const std::vector<std::string>& face);

	std::string m_path;
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<VertexCoordinate> m_vertexCoordinates;
	std::vector<VertexNormal> m_vertexNormals;
	std::vector<TextureCoordinate> m_textureCoordinates;
};
