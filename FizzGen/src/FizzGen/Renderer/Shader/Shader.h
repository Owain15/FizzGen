#pragma once

#include <string>
//#include <glm/glm.hpp>

namespace FizzGen
{
	class Shader
	{
		public:
			
			//Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
			virtual ~Shader() = default;

			static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;



			//virtual void UploadUniformBuffer() ;

	};
}
