#pragma once
#include <GLEW/glew.h>

class Texture
{
public:
	Texture();
	~Texture();
	GLuint GetID() const;
	Texture(const Texture&) = delete;
	Texture(Texture&& other) noexcept;
	Texture& operator=(Texture&& other) noexcept;
	Texture& operator=(const Texture& other) = delete;
	void Bind();
	void Unbind();
	void BufferData(int width, int height, unsigned char* data);

	
private:
	GLuint m_ID;
};
