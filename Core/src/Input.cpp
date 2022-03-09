#include "Input.h"

namespace Phantom
{

	Input* Input::_instance = nullptr;
	GLFWwindow* Input::_window = nullptr;

	Input::Input(GLFWwindow* window)
	{
		if (_instance != nullptr)
			return;

		_instance = this;
		_window = window;
	}

	void Input::UpdateKeys()
	{
		for (const auto& [k, v] : _controls)
		{
			//v.event?.invoke();
		}
	}

	bool Input::GetKey(int key, KeyState state)
	{
		if (glfwGetKey(_window, key) == state)
			return true;
		else
			return false;
	}
}


