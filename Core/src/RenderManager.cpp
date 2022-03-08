#include "RenderManager.h"
#include <glm/gtc/matrix_transform.hpp>

RenderManager::RenderManager()
{
	if (!_instance)
		_instance = this;

	_needsToUpdate = false;
	_proj = glm::perspective(glm::radians(50.0f), (float)_width / (float)_height, 0.1f, 100.0f);
}

RenderManager* RenderManager::Instance()
{
	return _instance;
}

void RenderManager::SetModelMatrix(glm::mat4 model)
{
	_model = model;
	_needsToUpdate = true;
}

void RenderManager::Update(Shader &shader)
{
	if(_needsToUpdate)
		_mvp = _proj * Camera::GetMainCamera()->ViewMatrix() * _model;
	shader.SendUniformData("mvp", _mvp);
}
