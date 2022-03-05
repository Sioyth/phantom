#include "Camera.h"

Camera* Camera::_mainCamera = nullptr;

Camera::Camera(Entity* entity) : Component(entity)
{
	if (!_mainCamera)
		_mainCamera = this;
};
