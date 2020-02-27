#include "Shaderprogram.h"

Shaderprogram::Shaderprogram() {
	m_ID = 0;
	std::cout << "Massive error, empty shader object created" << std::endl;
}

Shaderprogram::Shaderprogram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
	int success = 1;
	char infoLog[512] = "";
	const char* vShaderCode = vertexShaderSource.c_str();
	const char* fShaderCode = fragmentShaderSource.c_str();

	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "vShadercompilation failed with: " << infoLog << std::endl;
	}

	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
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

void Shaderprogram::Bind() const {
	glUseProgram(m_ID);
}

void Shaderprogram::UnBind() const {
	glUseProgram(0);
}

void Shaderprogram::SetModelMatrix(glm::mat4 modelMatrix) const {
	SetUniformMatrix4f("ModelMatrix", modelMatrix);
}

void Shaderprogram::SetProjectionMatrix(glm::mat4 projectionMatrix)  const {
	SetUniformMatrix4f("ProjectionMatrix", projectionMatrix);
}

void Shaderprogram::SetViewMatrix(glm::mat4 viewMatrix) const {
	SetUniformMatrix4f("ViewMatrix", viewMatrix);
}

void Shaderprogram::SetLightPosition(glm::vec3 position) const {
	SetUniform3f("lightPos", position);
}

void Shaderprogram::SetViewPosition(glm::vec3 position) const {
	SetUniform3f("viewPos", position);
}

void Shaderprogram::SetLightColor(glm::vec3 color) const {
	SetUniform3f("lightColor", color);
}

void Shaderprogram::SetObjectColor(glm::vec3 color) const {
	SetUniform3f("objectColor", color);
}

void Shaderprogram::SetTextureSampler(int i) const
{
	SetUniform1i("objectTexture", i);
}

void Shaderprogram::SetIsSun(bool value) const
{
	SetUniform1b("isSun", value);
}


void Shaderprogram::SetUniformMatrix4f(const char* identifier, glm::mat4 value) const {
	GLuint location = glGetUniformLocation(m_ID, identifier);
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

void Shaderprogram::SetUniform3f(const char* identifier, glm::vec3 value) const {
	GLuint location = glGetUniformLocation(m_ID, identifier);
	glUniform3fv(location, 1, &value[0]);
}

void Shaderprogram::SetUniform1i(const char* identifier, int i) const
{
	GLuint location = glGetUniformLocation(m_ID, identifier);
	glUniform1i(location, i);
}

void Shaderprogram::SetUniform1b(const char* identifier, bool value) const
{
	GLuint location = glGetUniformLocation(m_ID, identifier);
	glUniform1i(location, value);
}

Shaderprogram& Shaderprogram::operator= ( Shaderprogram&& other ) noexcept {
	std::swap ( m_ID, other.m_ID );
	return *this;
}
