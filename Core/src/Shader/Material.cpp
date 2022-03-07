#include "Material.h"

Material::Material()
{
	_color = glm::vec4(1.0f);
	_shader = Shader::GetDefault();
}

Shader* Material::GetShader()
{
	return _shader;
}


void Material::Apply()
{
	_shader->Use();
	_shader->SendUniformData("color", _color);
}
