#include "STBImage.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

STBImage::STBImage(unsigned char* data, int height, int width)
	:m_data(data), m_height(height), m_width(width)
{}

STBImage::STBImage(std::string path)
{
	stbi_set_flip_vertically_on_load(true);
	m_data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 0);
}

STBImage::~STBImage()
{
	if(m_data)
		stbi_image_free(m_data);
}

STBImage::STBImage(STBImage&& other) noexcept
{
	std::swap(m_data, other.m_data);
	std::swap(m_height, other.m_height);
	std::swap(m_width, other.m_width);
	std::swap(m_channels, other.m_channels);
}

STBImage& STBImage::operator=(STBImage&& other) noexcept
{
	std::swap(m_data, other.m_data);
	return *this;
}

unsigned char* STBImage::GetData() const
{
	return m_data;
}

int STBImage::GetHeight() const
{
	return m_height;
}

int STBImage::GetWidth() const
{
	return m_width;
}
