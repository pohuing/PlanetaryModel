#include "ObjParser.h"
#include <vector>
#include <string>
#include <iostream>

Parser::Parser(std::string path)
	:m_path(path) {}

void Parser::ReadFile() {
	std::ifstream vstream(m_path);
	std::stringstream vbuffer;
	vbuffer << vstream.rdbuf();
	Parse(vbuffer);
}

std::vector<Vertex> Parser::GetVertices() const
{
	return m_vertices;
}

std::vector<unsigned int> Parser::GetIndices() const
{
	return m_indices;
}

void Parser::Parse(std::stringstream& code){
	for(std::string line; std::getline(code, line);) {
		std::vector<std::string> words;
		std::string letter_buffer;
		if (line.length() > 0 && line[0] == '#')
		{
			continue;
		}
		for(auto letter : line)
		{
			if (letter == ' ')
			{
				words.push_back(letter_buffer);
				letter_buffer.clear();
			}else			
			letter_buffer += letter;
		}
		words.push_back(letter_buffer);
		ParseLine(words);
	}
}

void Parser::ParseLine(const std::vector<std::string>& words)
{
	if(words[0] == "v")
		ParseGeometricVertex(words);
	else if(words[0] == "vn")
		ParseVertexNormals(words);
	else if(words[0] == "vt")
		std::cout << "Encountered texture coordinate, not supported yet";
	else if(words[0] == "vp")
		std::cout << "Encountered free form geometry statement, not supported yet";
	else if(words[0] == "f")
		ParseFace(words);
	else {
		std::cout << "Encountered unexpected type of line:" << std::endl;
		for(const auto& word : words)
			std::cout << word << " ";
		std::cout << std::endl;
	}

}

void Parser::ParseGeometricVertex(const std::vector<std::string>& coordinates)
{
	if (coordinates.size() != 4)
	{
		std::cout << "Unexpected size of Vertex: " << coordinates.size() << " With values:" << std::endl;
		for(const auto& coordinate : coordinates)
			std::cout << coordinate << std::endl;
	}
	m_vertexCoordinates.emplace_back(
		stof(coordinates[1]),
		stof(coordinates[2]),
		stof(coordinates[3])
	);
}

void Parser::ParseVertexNormals(const std::vector<std::string>& normals)
{
	if(normals.size() != 4)
	{
		std::cout << "Unexpected size of Vertex: " << normals.size() << " With values:" << std::endl;
		for(const auto& normal : normals)
			std::cout << normal << std::endl;
	}
	m_vertexNormals.emplace_back(
		stof(normals[1]),
		stof(normals[2]),
		stof(normals[3])
	);
}

inline void Parser::ParseFace(const std::vector<std::string>& face)
{
	char buffer[10] = "";
	for (int i = 1; i < face.size(); i++)
	{
		auto word = face[i];
		auto v = word.substr(0, word.find('/'));
		auto texture_start = word.find('/') + 1;
		auto texture_end = word.find_last_of('/');
		auto t = std::string();
		if(texture_start == texture_end)
			t = "0";
		else
			t = word.substr(texture_start, word.find_last_of('/'));
		auto n = word.substr(word.find_last_of('/') + 1);
		auto vertex_index = stoi(v);
		auto texture_location = stoi(t);
		auto vertex_normal_index = stoi(n);

		// negative indices start from the back, positive at position 1
		if(vertex_index < 0)
			vertex_index = m_vertexCoordinates.size() - vertex_index;
		else
			vertex_index--;
		if(vertex_normal_index < 0)
			vertex_normal_index = m_vertexNormals.size() - vertex_normal_index;
		else
			vertex_normal_index--;

		// TODO: Optimize Vertex generation to prevent duplicate Vertex definitions
		// BUG: Vertex indices seem to be entirely wrong or incompatible with the shaders, malforming the models massively
		m_vertices.push_back(Vertex{ m_vertexCoordinates[vertex_index],m_vertexNormals[vertex_normal_index] });
		m_indices.push_back(m_vertices.size());
	}
}
