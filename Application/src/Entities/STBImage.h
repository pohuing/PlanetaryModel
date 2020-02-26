#pragma once
#include <memory>
#include <string>


class STBImage
{
public:
	STBImage() = default;
	STBImage(unsigned char* data, int height, int width);
	STBImage(std::string path);
	~STBImage();
	STBImage(const STBImage&) = delete;
	STBImage(STBImage&& other) noexcept;
	STBImage& operator=(STBImage&& other) noexcept;
	STBImage& operator=(const STBImage& other) = delete;
	
	unsigned char* GetData() const;
	int GetHeight() const;
	int GetWidth() const;
	
private:
	unsigned char* m_data = nullptr;
	int m_width = 0;
	int m_height = 0;
	int m_channels = 0;
};
