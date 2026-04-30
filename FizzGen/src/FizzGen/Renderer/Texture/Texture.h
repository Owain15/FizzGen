#pragma once

#include <string>
#include "FizzGen/Core.h"

namespace FizzGen
{
	class Texture
	{
		public:
			
			virtual ~Texture() = default;
		
			virtual uint32_t GetWidth() const = 0;
			virtual uint32_t GetHeight() const = 0;
			//GetFormat

			virtual void Bind(uint32_t slot = 0) const = 0;
			
			//static Ref<Texture> Create(const std::string& path);
			//static Ref<Texture> Create(uint32_t width, uint32_t height);
	};

	class Texture2D : public Texture
	{
		public:
			
			//virtual ~Texture2D() = default;
		
			static FizzGen::Ref<Texture2D> Create(const std::string& path);
			//static FizzGen::Ref<Texture2D> Create(uint32_t width, uint32_t height);
	
	};

}
