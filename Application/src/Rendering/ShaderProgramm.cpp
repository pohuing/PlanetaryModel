#include "ShaderProgramm.h"

Shaderprogramm::Shaderprogramm() {
	m_ID = 0;
	std::cout << "Massive error, empty shader object created" << std::endl;
}

Shaderprogramm::Shaderprogramm(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];
	const char* vShaderCode = vertexShaderSource.c_str();
	const char* fShaderCode = fragmentShaderSource.c_str();

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "vShadercompilation failed with: " << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "fShadercompilation failed with: " << infoLog << std::endl;
	}

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	glLinkProgram(m_ID);
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//cleanup
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shaderprogramm::Bind() const {
	glUseProgram(m_ID);
}

void Shaderprogramm::UnBind() const {
	glUseProgram(0);
}

void Shaderprogramm::SetModelMatrix(glm::mat4 modelMatrix) const {
	SetUniformMatrix4f("ModelMatrix", modelMatrix);
}

void Shaderprogramm::SetProjectionMatrix(glm::mat4 projectionMatrix)  const {
	SetUniformMatrix4f("ProjectionMatrix", projectionMatrix);
}

void Shaderprogramm::SetViewMatrix(glm::mat4 viewMatrix) const {
	SetUniformMatrix4f("ViewMatrix", viewMatrix);
}

void Shaderprogramm::SetLightPosition(glm::vec3 position) const {
	SetUniform3f("lightPos", position);
}

void Shaderprogramm::SetViewPosition(glm::vec3 position) const {
	SetUniform3f("viewPos", position);
}

void Shaderprogramm::SetLightColor(glm::vec3 color) const {
	SetUniform3f("lightColor", color);
}

void Shaderprogramm::SetObjectColor(glm::vec3 color) const {
	SetUniform3f("objectColor", color);
}

void Shaderprogramm::SetUniformMatrix4f(char* identifier, glm::mat4 value) const {
	GLuint location = glGetUniformLocation(m_ID, identifier);
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

void Shaderprogramm::SetUniform3f(char* identifier, glm::vec3 value) const {
	GLuint location = glGetUniformLocation(m_ID, identifier);
	glUniform3fv(location, 1, &value[0]);
}