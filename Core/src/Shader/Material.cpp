#include "Material.h"

Shader* Material::GetShader()
{
	return _shader;
}

Material::Material()
{
	_color = glm::vec4(1.0f);
	_shader = Shader::GetDefault();
}

void Material::Apply()
{
	_shader->Use();
	_shader->SendUniformData("color", _color);
}
