
#include "fgpch.h"
#include "FizzGen/Platform/ANGLE/Texture/ANGLETexture.h"

#include "stb_image.h"


namespace FizzGen
{
	ANGLETexture2D::ANGLETexture2D(const std::string& path)
		: m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		FG_CORE_ASSERT(data, "Failed to load texture image: {0}", path);
		
		m_Width = width;
		m_Height = height;
	
		GLenum internalFormat = (channels == 4) ? GL_RGBA8 : GL_RGB8;
		GLenum dataFormat = (channels == 4) ? GL_RGBA : GL_RGB;

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, m_Width, m_Height);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		glTexParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);
	}

	ANGLETexture2D::ANGLETexture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		FG_PROFILE_FUNCTION();

		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;
	
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTexStorage2D(GL_TEXTURE_2D, 1, m_InternalFormat, m_Width, m_Height);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glTexParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	ANGLETexture2D::~ANGLETexture2D()
	{
		FG_PROFILE_FUNCTION();
		glDeleteTextures(1, &m_RendererID);
	}

	void ANGLETexture2D::Bind(uint32_t slot) const
	{
		FG_PROFILE_FUNCTION();
		glActiveTexture(GL_TEXTURE0 + slot);                                                                               
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void ANGLETexture2D::SetData(void* data, uint32_t size)
	{
		FG_PROFILE_FUNCTION();
		uint32_t bpp = (m_DataFormat == GL_RGBA) ? 4 : 3;
		FG_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
	
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

}
