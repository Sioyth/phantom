#include "Shader.h"
#include <iostream>

namespace Phantom
{
	Shader* Shader::_defaultShader = nullptr;
	Shader* Shader::_currentShader = nullptr;
	Shader* Shader::_shaderGraphShader = nullptr;

	Shader::Shader(const char* vertexPath, const char* fragPath)
	{
		//LoadShaders(vertexPath, fragPath);
		std::string vertexCode = Load(vertexPath);
		std::string fragCode = Load(fragPath);

		CompileShaders(vertexCode.c_str(), fragCode.c_str());
	}

	void Shader::Use()
	{
		glUseProgram(_id);
		_currentShader = this;
	}

	unsigned int Shader::GetID()
	{
		return _id;
	}

	void Shader::SendUniformData(const char* name, float f)
	{
		glUniform1f(glGetUniformLocation(_id, name), f);
	}

	void Shader::SendUniformData(const char* name, glm::vec3 v)
	{
		glUniform3f(glGetUniformLocation(_id, name), v.x, v.y, v.z);
	}

	void Shader::SendUniformData(const char* name, glm::vec4 v)
	{
		glUniform4f(glGetUniformLocation(_id, name), v.x, v.y, v.z, v.w);
	}

	void Shader::SendUniformData(const char* name, glm::mat4 m)
	{
		glUniformMatrix4fv(glGetUniformLocation(_id, name), 1, GL_FALSE, &m[0][0]);
	}

	void Shader::SendUniformData(const char* name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(_id, name), x, y, z, w);
	}

	void Shader::LoadDefaultShaders()
	{
		_defaultShader = new Shader("src/shader/default.vert", "src/shader/default.frag");
	}
	std::string Shader::Load(const char* shaderPath)
	{
		//Get the source code from the file
		std::string shaderCodeString;
		std::ifstream shaderFile;

		// Enables exceptions on the ifstream so that the try catch block can be used
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			// Open files
			shaderFile.open(shaderPath);

			if (!shaderFile.is_open())
			{
				std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_OPENED" << std::endl;
				return nullptr; //if cannot find file, all of the time
			}

			std::stringstream shaderStream;

			// Read file buffer content into the streams
			shaderStream << shaderFile.rdbuf();

			// Close the file
			shaderFile.close();

			// Convert the stream into a string
			shaderCodeString = shaderStream.str();

		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		// Convert the string to a char array
		return shaderCodeString;
	}
	void Shader::LoadShaders(const char* vertexPath, const char* fragPath)
	{
		//Get the source code from the file
		std::string vertexCodeString;
		std::string fragmentCodeString;
		std::ifstream vertexShaderFile;
		std::ifstream fragmentShaderFile;

		// Enables exceptions on the ifstream so that the try catch block can be used
		vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);


		try
		{
			// Open files
			vertexShaderFile.open(vertexPath);
			fragmentShaderFile.open(fragPath);

			if (!vertexShaderFile.is_open())
			{
				std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_OPENED" << std::endl;
				return; //if cannot find file, all of the time
			}

			std::stringstream vertexShaderStream, fragmentShaderStream;

			// Read file's buffer content into the streams
			vertexShaderStream << vertexShaderFile.rdbuf();
			fragmentShaderStream << fragmentShaderFile.rdbuf();

			// Close the opened files
			vertexShaderFile.close();
			fragmentShaderFile.close();

			// Convert the stream into a string
			vertexCodeString = vertexShaderStream.str();
			fragmentCodeString = fragmentShaderStream.str();

		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		// Convert the string to a char array
		const char* vertexShaderCode = vertexCodeString.c_str();
		const char* fragmentShaderCode = fragmentCodeString.c_str();

		CompileShaders(vertexShaderCode, fragmentShaderCode);
	}
	void Shader::CompileShaders(const char* vertexCode, const char* fragCode)
	{
		// Compile Shaders
		unsigned int vertex, fragment;
		int sucess;
		char infoLog[512];

		// - Compile Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexCode, NULL);
		glCompileShader(vertex);

		glad_glGetShaderiv(vertex, GL_COMPILE_STATUS, &sucess);

		if (!sucess)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// - Compile Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragCode, NULL);
		glCompileShader(fragment);

		glad_glGetShaderiv(fragment, GL_COMPILE_STATUS, &sucess);

		if (!sucess)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		_id = glCreateProgram();
		glAttachShader(_id, vertex);
		glAttachShader(_id, fragment);
		glLinkProgram(_id);

		//Link Shaders
		glGetProgramiv(_id, GL_LINK_STATUS, &sucess);

		if (!sucess)
		{
			glGetProgramInfoLog(_id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		// Delete shaders they are no longer needed as the program has the shader already and has linked them
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		_currentShader = this;
	}
	Shader& Shader::CurrentShader()
	{
		return *_currentShader;
	}
}
