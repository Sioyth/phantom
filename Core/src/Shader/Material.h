#ifndef MATERIAL_H
#define MATERIAL_H

#include <map>
#include "Shader.h"
#include "UniformValue.h"

class Material
{
	public:

		Material();
		void Apply(); // USE instead?
		Shader* GetShader();

	private:
		Shader* _shader;
		glm::vec4 _color;
		std::map<std::string, UniformValue> _uniforms;
};

#endif

