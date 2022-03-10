#ifndef MATERIAL_H
#define MATERIAL_H

#include <map>
#include "Shader.h"
#include "UniformValue.h"

namespace Phantom
{
	class Material
	{
		public:

			Material();
			void Apply(); // USE instead?
			Shader& GetShader();

		private:
			Shader* _shader;
			glm::vec3 _color;
			float _ambientReflectance;
			float _diffuseReflectance;
			float _specularExponent;
			float _specularReflectance;
			std::map<std::string, UniformValue> _uniforms;
	};

}

#endif

