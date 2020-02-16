#pragma once
#include <GLEW/glew.h>

class IndexBufferObject {
public:
	IndexBufferObject();
	~IndexBufferObject();
	void Bind();
	void Unbind();
	void IndexBufferObject::BufferData(GLenum target, GLsizei size, const GLvoid* data, GLenum usage);
	GLsizei GetIndicesCount();
private:
	GLuint m_IBO;
	GLsizei m_VerticesCount;
};