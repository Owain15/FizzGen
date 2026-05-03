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

			static FizzGen::Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
			static FizzGen::Ref<Shader> Create(const std::string& filepath);

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			virtual const std::string& GetName() const = 0;

			//virtual void UploadUniformBuffer() ;

	};

	class ShaderLibrary
	{
		public:
		
			void Add(const FizzGen::Ref<Shader>& shader);
			void Add(const std::string& name, const FizzGen::Ref<Shader>& shader);
			
		
			FizzGen::Ref<Shader> Load(const std::string& filepath);
			FizzGen::Ref<Shader> Load(const std::string& name, const std::string& filepath);
			
			FizzGen::Ref<Shader> Get(const std::string& name);
	
			bool Exists(const std::string& name) const;

		private:
	
			std::unordered_map<std::string, FizzGen::Ref<Shader>> m_Shaders;
	
	};
}
