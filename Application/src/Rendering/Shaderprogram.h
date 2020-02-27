#pragma once
#include <string>
#include <GLEW/glew.h>
#include <iostream>
#include <GLM/glm.hpp>

class Shaderprogram {
public:
	Shaderprogram();
	Shaderprogram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
	Shaderprogram(Shaderprogram const&) = delete;
	Shaderprogram& operator=(Shaderprogram&& other) noexcept;
	void Bind() const;
	void UnBind() const;
	void SetModelMatrix(glm::mat4 modelMatrix) const;
	void SetProjectionMatrix(glm::mat4 projectionMatrix) const;
	void SetViewMatrix(glm::mat4 viewMatrix)const;

	void SetLightPosition(glm::vec3 position) const;
	void SetViewPosition(glm::vec3 position) const;
	void SetLightColor(glm::vec3 color) const;
	void SetObjectColor(glm::vec3 color) const;
	void SetTextureSampler(int i) const;
	void SetIsSun(bool value) const;
	
	unsigned int m_ID = 0;
private:
	void SetUniform1b(const char* identifier, bool value) const;
	void SetUniformMatrix4f(const char* identifier, glm::mat4 value) const;
	void SetUniform3f(const char* identifier, glm::vec3 value) const;
	void SetUniform1i(const char* identifier, int i) const;
};
