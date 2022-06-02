#include "EditorCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../util/Input.h"

Phantom::EditorCamera::EditorCamera(float aspect, float fov)
{
	_fov = fov;
	_speed = 5.0f;
	_aspectRatio = aspect;
	_position = glm::vec3(0.0f);
	_forward = glm::vec3(0.0f, 0.0f, -1.0f);
	
	_proj = glm::perspective(glm::radians(_fov), _aspectRatio, 0.1f, 100.0f);
	_view = glm::lookAt(_position, _position + _forward, _up);
	UpdateDirs();
}

void Phantom::EditorCamera::Translate(const glm::vec3& translation)
{
	_position += translation;
}

const glm::mat4& Phantom::EditorCamera::Proj()
{
	return glm::perspective(glm::radians(_fov), _aspectRatio, 0.1f, 100.0f);
}
const glm::mat4& Phantom::EditorCamera::View()
{
	_view = glm::lookAt(_position, _position + _forward, _up);
	return _view;
}

void Phantom::EditorCamera::Update(const float& dt)
{
	if (!Input::Instance()->GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT, KeyState::PRESS))
		return;

	static bool firstPass = true;
	static float lastX;
	static float lastY;
	static float yaw, pitch;

	if (Input::Instance()->GetKey(GLFW_KEY_W, KeyState::PRESS))
		Translate(_forward * _speed * dt);
	if (Input::Instance()->GetKey(GLFW_KEY_S, KeyState::PRESS))
		Translate(-_forward * _speed * dt);
	if (Input::Instance()->GetKey(GLFW_KEY_A, KeyState::PRESS))
		Translate(-_right * _speed * dt);
	if (Input::Instance()->GetKey(GLFW_KEY_D, KeyState::PRESS))
		Translate(_right * _speed * dt);
	//
	if (Input::Instance()->GetKey(GLFW_KEY_Q, KeyState::PRESS))
		Translate(-_up * _speed * dt);
	if (Input::Instance()->GetKey(GLFW_KEY_E, KeyState::PRESS))
		Translate(_up * _speed * dt);

	float xpos = Input::Instance()->GetMousePos().x;
	float ypos = Input::Instance()->GetMousePos().y;
	if (firstPass)
	{
		lastX = xpos;
		lastY = ypos;
		firstPass = false;
		yaw = -90.0f;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	_forward = glm::normalize(direction);

	UpdateDirs();
}

void Phantom::EditorCamera::UpdateDirs()
{
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	_right = glm::normalize(glm::cross(_forward, up));
	_up = glm::cross(_right, _forward);
}
