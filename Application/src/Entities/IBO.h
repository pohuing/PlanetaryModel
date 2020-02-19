#pragma once
#include <GLEW/glew.h>

class IndexBufferObject {
public:
	IndexBufferObject();
	~IndexBufferObject();
	IndexBufferObject(const IndexBufferObject&) = delete;
	IndexBufferObject(IndexBufferObject&& other) noexcept;
	IndexBufferObject& operator=(IndexBufferObject&& other) noexcept;
	IndexBufferObject& operator=(const IndexBufferObject& other) = delete;
	void Bind() const;
	static void Unbind();
	void BufferData(GLenum target, GLsizei size, const GLvoid* data, GLenum usage);
	GLsizei GetIndicesCount() const;
private:
	GLuint m_IBO;
	GLsizei m_VerticesCount;
};
