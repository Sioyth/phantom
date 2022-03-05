#include "Material.h"

Shader* Material::GetShader()
{
	return _shader;
}

void Material::Apply()
{
	_shader->Use();
}
