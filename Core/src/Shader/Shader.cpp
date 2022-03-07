#include "Shader.h"
#include <iostream>

Shader* Shader::_defaultShader = nullptr;

Shader::Shader(const char* vertexPath, const char* fragPath)
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

	// Compile Shaders
	unsigned int vertex, fragment;
	int sucess;
	char infoLog[512];

	// - Compile Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderCode, NULL);
	glCompileShader(vertex);

	glad_glGetShaderiv(vertex, GL_COMPILE_STATUS, &sucess);

	if (!sucess)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// - Compile Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
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
}

void Shader::Use()
{
	glUseProgram(_id);
}

unsigned int Shader::GetID()
{
	return _id;
}

void Shader::SendUniformData(const char* name, float f)
{
	unsigned int loc = glGetUniformLocation(_id, name);
	glUniform1f(loc, f);
}

void Shader::SendUniformData(const char* name, glm::vec4 v)
{
	unsigned int location = glGetUniformLocation(_id, name);
	glUniform4f(location, v.x, v.y, v.z, v.w);

	//SetVec4(name, v.x, v.y, v.z, v.w)
}

void Shader::SendUniformData(const char* name, float x, float y, float z, float w)
{
	unsigned int location = glGetUniformLocation(_id, name);
	glUniform4f(location, x, y, z, w);
}

void Shader::LoadDefaultShaders()
{
	// TODO: Fix this fucking paths
	_defaultShader = new Shader("D:\\Dev\\repos\\phantom\\Core\\src\\Shader\\default.vert", "D:\\Dev\\repos\\phantom\\Core\\src\\Shader\\default.frag");
}
