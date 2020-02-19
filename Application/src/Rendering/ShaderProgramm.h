#pragma once
#include <string>
#include <GLEW/glew.h>
#include <iostream>
#include <GLM/glm.hpp>

class Shaderprogramm {
public:
	Shaderprogramm();
	Shaderprogramm(const std::string& vertexSource, const std::string& fragmentShader);
	Shaderprogramm(Shaderprogramm const&) = delete;
	Shaderprogramm& operator=(Shaderprogramm&& other);
	void Bind() const;
	void UnBind() const;
	void SetModelMatrix(glm::mat4 modelMatrix) const;
	void SetProjectionMatrix(glm::mat4 projectionMatrix) const;
	void SetViewMatrix(glm::mat4 viewMatrix)const;

	void SetLightPosition(glm::vec3 position) const;
	void SetViewPosition(glm::vec3 position) const;
	void SetLightColor(glm::vec3 color) const;
	void SetObjectColor(glm::vec3 color) const;

	unsigned int m_ID = 0;
private:
	void SetUniformMatrix4f(const char* identifier, glm::mat4 value) const;
	void SetUniform3f(const char* identifier, glm::vec3 value) const;
};
