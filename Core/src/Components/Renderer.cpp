#include "Renderer.h"
#include "Transform.h"

Renderer::Renderer(Entity* entity) : Component(entity)
{
	_model = nullptr;
	_material = new Material();
};

void Renderer::Update()
{
	_material->Apply();
	if (_model)
	{
		//_material->GetShader()->SendUniformData("mvp", _entity->GetComponent<Transform>()->Matrix());
		_model->Draw(*_material->GetShader());
	}

}
