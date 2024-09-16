#include "Texture.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "iostream"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
	:m_Texture(0)
{}


Texture::Texture(std::string texturePath)
{
	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	const char* path = texturePath.c_str();
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Error::Texture::Failed_to_Load_Texture" << std::endl;
	}
	stbi_image_free(data);
}

Texture::Texture(std::string path, const std::string& directory, bool gamma)
{
	path = directory + '/' + path;

	glGenTextures(1, &m_Texture);
	
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format = 1;
		if (nrChannels == 1)
		{
			format = GL_RED;
		}
		else if (nrChannels == 3)
		{
			format = GL_RGB;
		}
		else if (nrChannels == 4)
		{
			format = GL_RGBA;
		}
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Error::Texture::Failed_to_Load_Texture" << std::endl;
	}
	stbi_image_free(data);
}

unsigned int Texture::texture() const
{
	return this->m_Texture;
}

std::string Texture::type() const
{
	return m_type;
}

void Texture::type(std::string t)
{
	this->m_type = t;
}

aiString Texture::path() const
{
	return this->m_Path;
}

void Texture::path(aiString p)
{
	this->m_Path = p;
}

