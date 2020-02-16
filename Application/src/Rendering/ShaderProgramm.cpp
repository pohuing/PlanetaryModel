#include "ShaderProgramm.h"

Shaderprogramm::Shaderprogramm()
{
	m_ID = 0;
	std::cout << "Massive error, empty shader object created" << std::endl;
}

Shaderprogramm::Shaderprogramm(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];
	const char* vShaderCode = vertexShaderSource.c_str();
	const char* fShaderCode = fragmentShaderSource.c_str();

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "vShadercompilation failed with: " << infoLog << std::endl;
	}


	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "fShadercompilation failed with: " << infoLog << std::endl;
	}

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	glLinkProgram(m_ID);
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//cleanup
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shaderprogramm::Bind() const
{
	glUseProgram(m_ID);
}

void Shaderprogramm::UnBind() const
{
	glUseProgram(0);
}

void Shaderprogramm::SetModelMatrix(glm::mat4 modelMatrix) const
{
	GLuint location = glGetUniformLocation(m_ID, "ModelMatrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, &modelMatrix[0][0]);
}

void Shaderprogramm::SetProjectionMatrix(glm::mat4 projectionMatrix)  const
{
	GLuint location = glGetUniformLocation(m_ID, "ProjectionMatrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void Shaderprogramm::SetViewMatrix(glm::mat4 viewMatrix) const
{
	GLuint location = glGetUniformLocation(m_ID, "ViewMatrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, &viewMatrix[0][0]);
}
