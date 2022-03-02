#ifndef SHADER_h
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <glm/glm.hpp>

class Shader
{
	public:
		unsigned int GetID();
		Shader(const char* vertexPath, const char* fragPath);

		void Use();
		void Delete(); // Redundant?

		void SendUniformData(const char* name, glm::vec4 v);
		void SendUniformData(const char* name, float x, float y, float z, float w = 1.0f);

	private:
		unsigned int _id;

};




#endif
