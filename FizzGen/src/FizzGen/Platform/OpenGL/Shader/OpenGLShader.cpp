
#include "fgpch.h"

#include "OpenGLShader.h"

#include <fstream>

#ifdef FG_USE_ANGLE
#include <GLES3/gl3.h>
#else
#include <glad/glad.h>
#endif

#include <glm/gtc/type_ptr.hpp>


//public
namespace FizzGen
{
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		auto shaderSources = std::unordered_map<GLenum, std::string>
		{
			{ GL_VERTEX_SHADER, vertexSrc },
			{ GL_FRAGMENT_SHADER, fragmentSrc }
		};

		Compile(shaderSources);

		//// Create an empty vertex shader handle
		//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		//// Send the vertex shader source code to GL
		//// Note that std::string's .c_str is NULL character terminated.
		//const GLchar* source = vertexSrc.c_str();
		//glShaderSource(vertexShader, 1, &source, 0);

		//// Compile the vertex shader
		//glCompileShader(vertexShader);

		//GLint isCompiled = 0;
		//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

		//if (isCompiled == GL_FALSE)
		//{
		//	GLint maxLength = 0;
		//	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		//	// The maxLength includes the NULL character
		//	std::vector<GLchar> infoLog(maxLength);
		//	glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		//	// We don't need the shader anymore.
		//	glDeleteShader(vertexShader);

		//	//log error
		//	FG_CORE_ERROR("Vertex shader compilation failed: {0}", infoLog.data());
		//	FG_CORE_ASSERT(false, "Vertex shader compilation failed");

		//	return;
		//}



		//// Create an empty fragment shader handle
		//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//// Send the fragment shader source code to GL
		//// Note that std::string's .c_str is NULL character terminated.
		//source = fragmentSrc.c_str();
		//glShaderSource(fragmentShader, 1, &source, 0);

		//// Compile the fragment shader
		//glCompileShader(fragmentShader);

		//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);

		//if (isCompiled == GL_FALSE)
		//{
		//	GLint maxLength = 0;
		//	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		//	// The maxLength includes the NULL character
		//	std::vector<GLchar> infoLog(maxLength);
		//	glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		//	// We don't need the shader anymore.
		//	glDeleteShader(fragmentShader);
		//	// Either of them. Don't leak shaders.
		//	glDeleteShader(vertexShader);

		//	//log error
		//	FG_CORE_ERROR("Fragment shader compilation failed: {0}", infoLog.data());
		//	FG_CORE_ASSERT(false, "Fragment shader compilation failed");

		//	return;
		//}




		//// Vertex and fragment shaders are successfully compiled.
		//// Now time to link them together into a program.
		//// Get a program object.
		//m_RendererID = glCreateProgram();

		//// Attach our shaders to our program
		//glAttachShader(m_RendererID, vertexShader);
		//glAttachShader(m_RendererID, fragmentShader);

		//// Link our program
		//glLinkProgram(m_RendererID);

		//// Note the different functions here: glGetProgram* instead of glGetShader*.
		//GLint isLinked = 0;
		//glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);

		//if (isLinked == GL_FALSE)
		//{
		//	GLint maxLength = 0;
		//	glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

		//	// The maxLength includes the NULL character
		//	std::vector<GLchar> infoLog(maxLength);
		//	glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

		//	// We don't need the program anymore.
		//	glDeleteProgram(m_RendererID);
		//	// Don't leak shaders either.
		//	glDeleteShader(vertexShader);
		//	glDeleteShader(fragmentShader);

		//	FG_CORE_ERROR("Shader program linking failed: {0}", infoLog.data());
		//	FG_CORE_ASSERT(false, "Shader program linking failed");

		//	return;
		//}

		//// Always detach shaders after a successful link.
		//glDetachShader(m_RendererID, vertexShader);
		//glDetachShader(m_RendererID, fragmentShader);

	}


	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		
		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		std::string vertexSrc;
		std::string fragmentSrc;

		Compile(shaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, const float& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}


}


//private
namespace FizzGen
{
	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLuint program = glCreateProgram();
		std::vector<GLuint> shaderIDs(shaderSources.size());

		for (auto& shader : shaderSources)
		{
			GLenum shaderType = shader.first;
			const std::string& shaderSource = shader.second;
			
			GLuint shaderID = glCreateShader(shaderType);
			
			const GLchar* shaderSourceCStr = shaderSource.c_str();
			glShaderSource(shaderID, 1, &shaderSourceCStr, nullptr);
			
			glCompileShader(shaderID);
			GLint isCompiled = 0;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);
				glDeleteShader(shaderID);
				FG_CORE_ERROR("Shader compilation failed: {0}", infoLog.data());
				FG_CORE_ASSERT(false, "Shader compilation failed");
	
				//return;
				break;
			}
			
			glAttachShader(program, shaderID);
			shaderIDs.push_back(shaderID);

		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);

		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
			
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			glDeleteProgram(program);
			
			for (auto id : shaderIDs)
				glDeleteShader(id);
			FG_CORE_ERROR("Shader program linking failed: {0}", infoLog.data());
			FG_CORE_ASSERT(false, "Shader program linking failed");

			return;
		}

		for (auto id : shaderIDs)
			glDetachShader(program, id);

		
		m_RendererID = program;
	
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		std::string result;

		if (in)
		{
	// Get the size of the file
			in.seekg(0, std::ios::end);
	// Set the size of the result string to the size of the file
			result.resize(in.tellg());
	// Reset the position of the file pointer to the beginning of the file
			in.seekg(0, std::ios::beg);

	// Read the contents of the file into the result string
			in.read(&result[0], result.size());
	//Close the file
			in.close();

		}
		else
		{
			//FG_CORE_ASSERT(false, "Could not open file");
			FG_CORE_ERROR("Could not open file : '{0}'", filepath);
		}
		
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;


		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);


		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			FG_CORE_ASSERT(eol != std::string::npos, "Syntax error");
		
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			FG_CORE_ASSERT(type == "vertex" || type == "fragment" || type == "pixel", "Invalid shader type specified");
			
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			FG_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	GLenum OpenGLShader::ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
		{ 
			return GL_VERTEX_SHADER;
		}

		if (type == "fragment" || type == "pixel")
		{
			return GL_FRAGMENT_SHADER;
		}

		FG_CORE_ASSERT(false, "Unknown shader type!");
		
		return 0;
	}


}
