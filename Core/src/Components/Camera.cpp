#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Phantom
{
	Camera::Camera()
	{
		_fov = 50.0f;
		_view = glm::mat4(1.0f);
		_proj = glm::mat4(1.0f);
		_clippingPlanes = glm::vec2(0.1f, 100.0f); // near fars
		_projection = CameraProjection::Perspective;
	}

	void Camera::CalculateMatrices(Transform& transform)
	{
		switch (_projection)
		{
		case CameraProjection::Perspective:
			_proj = glm::perspective(glm::radians(_fov), 800.0f / 600.0f, _clippingPlanes.x, _clippingPlanes.y);
			break;
		case CameraProjection::Ortographic:
			//_proj = glm::ortho();
			break;
		}

		glm::vec3 target = transform.position() + transform.forward();
		_view = glm::lookAt(transform.position(), target, transform.up());
	}
}