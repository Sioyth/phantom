#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <glm/glm.hpp>

namespace Phantom
{
	class Shader
	{
	public:
		unsigned int GetID();
		Shader(const char* vertexPath, const char* fragPath);

		void Use();
		void Delete(); // Redundant?

		void SendUniformData(const char* name, float f);
		void SendUniformData(const char* name, glm::vec4 v);
		void SendUniformData(const char* name, glm::mat4 m);
		void SendUniformData(const char* name, float x, float y, float z, float w = 1.0f);

		static void LoadDefaultShaders();
		inline static void UseDefault() { _defaultShader->Use(); };
		inline static Shader& GetDefault() { return *_defaultShader; };
		inline static const unsigned int& GetDefaultID() { return _defaultShader->_id; }

	private:
		unsigned int _id;
		static Shader* _defaultShader; // TEMP - change this to stack rather than a pointer

	};

}
#endif
