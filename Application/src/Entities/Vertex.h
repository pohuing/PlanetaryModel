#pragma once
#include <GLM/glm.hpp>

class Vertex {
public:
// 	Vertex(glm::vec3 position, glm::vec3 normal);
	glm::vec3 m_Position;
	glm::vec3 m_Normal;
	glm::vec3 m_TexCoord;
};
