#include <glm/gtx/transform.hpp>
#include "Transform.h"
Transform::Transform()
{
	// Identity
	_scale = glm::vec3(1.0f);
	_rotation = glm::vec3(0.0f);
	_position = glm::vec3(1.0f);
	_transformMatrix = glm::mat4(1.0f);
}

void Transform::Scale(glm::vec3 scale)
{
	glm::scale(_transformMatrix, scale);
}

void Transform::Rotate(glm::vec3 rotation)
{
	//glm::rotate()
}

void Transform::Translate(glm::vec3 translation)
{
	glm::translate(_transformMatrix, translation);
}

void Transform::Update()
{
}

