#include "Camera.h"
#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
Camera* Camera::_mainCamera = nullptr;

Camera::Camera(Entity* entity) : Component(entity)
{
	if (!_mainCamera)
		_mainCamera = this;

	_viewMatrix = glm::lookAt(_entity->GetComponent<Transform>()->Position(), _entity->GetComponent<Transform>()->Position() + _entity->GetComponent<Transform>()->Forward(), _entity->GetComponent<Transform>()->Up());
}
void Camera::Update()
{
	// If it's not the main camera we don't need to update the viewMatrix even if it moves;
	if (_mainCamera != this)
		return;

	// Only recalculate view matrix if position has changed;
	static glm::vec3 lastPos = _entity->GetComponent<Transform>()->Position();
	if(_entity->GetComponent<Transform>()->Position() != lastPos)
		_viewMatrix = glm::lookAt(_entity->GetComponent<Transform>()->Position(), _entity->GetComponent<Transform>()->Position() + _entity->GetComponent<Transform>()->Forward(), _entity->GetComponent<Transform>()->Up());
}

const glm::mat4x4& Camera::ViewMatrix()
{
	return _viewMatrix;
}


