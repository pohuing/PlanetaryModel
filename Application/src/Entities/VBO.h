#pragma once
#include <GLEW/glew.h>

class VertexBufferObject {
public:
	VertexBufferObject();
	~VertexBufferObject();
	void Bind();
	void Unbind();
	void BufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
private:
	//VertexBufferObject(const VertexBufferObject& other);
	GLuint m_VBO;
};