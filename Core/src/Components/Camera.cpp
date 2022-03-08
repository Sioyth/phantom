#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
namespace Phantom
{
	const glm::mat4x4& Camera::ViewMatrix()
	{
		// Only recalculate view matrix if position has changed;
		//if (_entity->GetComponent<Transform>()->Position() != _lastPos)
		//_viewMatrix = glm::lookAt(_entity->GetComponent<Transform>()->Position(), _entity->GetComponent<Transform>()->Position() + _entity->GetComponent<Transform>()->Forward(), _entity->GetComponent<Transform>()->Up());
		/*glm::vec3 pos = _entity->GetComponent<Transform>()->Position();
		glm::vec3 forward = _entity->GetComponent<Transform>()->Forward();

		_viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
		*/
		return _viewMatrix;
	}
	void Camera::SetPerspective()
	{
	}
}


