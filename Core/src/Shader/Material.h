#ifndef MATERIAL_H
#define MATERIAL_H

#include <map>
#include "Shader.h"
#include "UniformValue.h"

class Material
{
	public:

		Material();
		Shader* GetShader();

	private:
		std::map<std::string, UniformValue> _uniforms;
		Shader* _shader;
		glm::vec4 _color;
		std::map<std::string, int> _uniforms;
};

#endif

