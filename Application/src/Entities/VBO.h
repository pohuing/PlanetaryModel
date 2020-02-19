#pragma once
#include <GLEW/glew.h>

class VertexBufferObject {
public:
	VertexBufferObject();
	~VertexBufferObject();
	VertexBufferObject(const VertexBufferObject&) = delete;
	VertexBufferObject(VertexBufferObject&& other);
	VertexBufferObject& operator=(VertexBufferObject&& other);
	void Bind();
	void Unbind();
	void BufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
private:
	//VertexBufferObject(const VertexBufferObject& other);
	GLuint m_VBO;
};
