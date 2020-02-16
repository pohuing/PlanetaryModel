#pragma once
#include <string>
#include <GLEW/glew.h>
#include <iostream>
#include <GLM/glm.hpp>

class Shaderprogramm {
public:
	Shaderprogramm();
	Shaderprogramm(const std::string &vertexSource, const std::string &fragmentShader);
	void Bind() const;
	void UnBind() const;
	void SetModelMatrix(glm::mat4 modelMatrix) const;
	void SetProjectionMatrix(glm::mat4 projectionMatrix) const;
	void SetViewMatrix(glm::mat4 viewMatrix)const;

	unsigned int m_ID;
private:
	/*Shaderprogramm(Shaderprogramm const&) = delete;
	Shaderprogramm& operator=(Shaderprogramm const&) = delete;*/
};