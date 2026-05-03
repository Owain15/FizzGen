#pragma once

#include "FizzGen/Renderer/Shader/Shader.h"

//math lib
#include <glm/glm.hpp>

// to remove
typedef unsigned int GLenum;

namespace FizzGen
{
	class OpenGLShader : public Shader
	{
		public:

			OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
			OpenGLShader(const std::string& filepath);
			
			virtual~OpenGLShader();

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual const std::string& GetName() const override { return m_Name; }

			void UploadUniformInt(const std::string& name, int value);

			void UploadUniformFloat (const std::string& name, const float& value);
			void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
			void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
			void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
			
			void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
			void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

		private:

			void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

			std::string ReadFile(const std::string& filepath);

			std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

			static GLenum ShaderTypeFromString(const std::string& type);

		private:

			uint32_t m_RendererID = 0;
			std::string m_Name;
	};
}
