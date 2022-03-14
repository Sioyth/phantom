#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

Phantom::Transform::Transform()
{
	_matrix = glm::mat4(1.0f);
	_scale = glm::vec3(1.0f);
	_rotation = glm::vec3(0.0f);
	_position = glm::vec3(0.0f);
}

Phantom::Transform::Transform(const Transform& other)
{
	_matrix = other._matrix;
	_scale = other._scale;
	_rotation = other._rotation;
	_position = other._position;;
}

void Phantom::Transform::Scale(const glm::vec3& scale)
{
	_scale = scale;
	_matrix = glm::scale(_matrix, scale);
}

void Phantom::Transform::Rotate(const glm::vec3& axis, const float& angle)
{
	//_rotation += rotation;
	_matrix = glm::rotate(_matrix, angle, axis);
}

void Phantom::Transform::Translate(const glm::vec3& translation)
{
	_position += translation;
	_matrix = glm::translate(_matrix, translation);
}

//		     0     1     2     4       	RT = right
//		0 [RT.x][UP.x][BK.x][POS.x]		UP = up
//		1 [RT.y][UP.y][BK.y][POS.y]		BK = back
//		2 [RT.z][UP.z][BK.z][POS.Z]		POS = position / translation
//		3 [    ][    ][    ][ US  ]		US = uniform scale

const glm::vec3& Phantom::Transform::up()
{
	return glm::normalize(glm::vec3(_matrix[1]));
}

const glm::vec3& Phantom::Transform::right()
{
	return glm::normalize(glm::vec3(_matrix[0]));
}

const glm::vec3& Phantom::Transform::forward()
{
	return glm::normalize(glm::vec3(_matrix[2].x, _matrix[2].y, -_matrix[2].z));
}

void Phantom::Transform::LookAt(glm::vec3 forward)
{
	_matrix = glm::lookAt(_position, _position + forward, up());
}
