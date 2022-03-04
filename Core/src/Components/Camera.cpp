#include "Camera.h"

Camera::Camera(Entity* entity) : Component(entity)
{
	//if (!_mainCamera) _mainCamera = this;
};

Camera* Camera::GetMainCamera()
{
	//return _mainCamera;
	return nullptr;
}

void Camera::SetMainCamera()
{
	//_mainCamera = this;
}
