#ifndef MATERIAL_H
#define MATERIAL_H

#include <map>
#include "Shader.h"

namespace Phantom
{
	class Material
	{
		public:

			Material();
			void Apply(); // USE instead?
			Shader& GetShader();
			inline void SetShader(Shader* shader) { _shader = shader; };
			inline void SetColor(const glm::vec3& color) { _color = color; };

		private:
			Shader* _shader;
			glm::vec3 _color;
			float _ambientReflectance;
			float _diffuseReflectance;
			float _specularExponent;
			float _specularReflectance;
	};

}

#endif

