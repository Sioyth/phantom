#include "Material.h"

namespace Phantom
{
	Material::Material()
	{
		_color = glm::vec3(1.0f, 1.0f, 1.0f);
		_shader = &Shader::GetDefault();
		_ambientReflectance = 1.0f;
		_diffuseReflectance = 0.5f;
		_specularReflectance = 0.7f;
		_specularExponent = 20.0f;
	}

	Shader& Material::GetShader()
	{
		return *_shader;
	}

	void Material::Apply()
	{
		_shader->SendUniformData("_material._color", _color);
		_shader->SendUniformData("_material._ambientReflectance", _ambientReflectance);
		_shader->SendUniformData("_material._diffuseReflectance", _diffuseReflectance);
		_shader->SendUniformData("_material._specularReflectance", _specularReflectance);
		_shader->SendUniformData("_material._specularExponent", _specularExponent);
		//_shader->SendUniformData("_albedo", _color, true);
	}
}
