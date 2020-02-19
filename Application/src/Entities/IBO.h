#pragma once
#include <GLEW/glew.h>

class IndexBufferObject {
public:
	IndexBufferObject();
	~IndexBufferObject();
	IndexBufferObject(const IndexBufferObject&) = delete;
	IndexBufferObject(IndexBufferObject&& other);
	IndexBufferObject& operator=(IndexBufferObject&& other);
	void Bind();
	void Unbind();
	void BufferData(GLenum target, GLsizei size, const GLvoid* data, GLenum usage);
	GLsizei GetIndicesCount();
private:
	GLuint m_IBO;
	GLsizei m_VerticesCount;
};
