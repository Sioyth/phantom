#include "Renderer.h"

Renderer::Renderer(Entity* entity) : Component(entity)
{
	_model = nullptr;
	_material = new Material();
};

void Renderer::Update()
{
	if(_model) 
		_model->Draw(*_material->GetShader());

	_material->Apply();

}
