#pragma once

#include "FizzGen/Renderer/Texture/Texture.h"

#include <GLES3/gl3.h>

namespace FizzGen
{
	class ANGLETexture2D : public Texture2D
	{
		public:
	
			ANGLETexture2D(const std::string& path);
			ANGLETexture2D(uint32_t width, uint32_t height);
			virtual ~ANGLETexture2D();
			
			virtual uint32_t GetWidth() const override { return m_Width; }
			virtual uint32_t GetHeight() const override { return m_Height; }
			
			virtual void Bind(uint32_t slot = 0) const override;

			virtual void SetData(void* data, uint32_t size) override;
	
		private:
	
			std::string m_Path;
			uint32_t m_RendererID;
			uint32_t m_Width, m_Height;

			GLenum m_InternalFormat, m_DataFormat;
	};
}
