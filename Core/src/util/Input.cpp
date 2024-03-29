#include "Input.h"

namespace Phantom
{

	Input* Input::_instance = nullptr;
	GLFWwindow* Input::_window = nullptr;

	void Input::PollEvents()
	{
		glfwPollEvents();
	}

	void Input::UpdateKeys()
	{
		for (const auto& [k, v] : _controls)
		{
			//v.event?.invoke();
		}
	}

	const glm::vec2& Input::GetMousePos()
	{
		double xpos, ypos;
		glfwGetCursorPos(_window, &xpos, &ypos);
		return glm::vec2(xpos, ypos);
	}

	bool Input::GetKey(int key, KeyState state)
	{
		if (glfwGetKey(_window, key) == state)
			return true;
		else
			return false;
	}
	bool Input::GetMouseButton(int key, KeyState state)
	{
		if (glfwGetMouseButton(_window, key) == state)
			return true;
		else
			return false;
		return false;
	}
	Input* Input::Instance()
	{
		if (_instance == nullptr)
			_instance = new Input();
		return _instance;
	}
}


