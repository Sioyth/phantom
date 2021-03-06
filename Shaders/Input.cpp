#include "Input.h"
#include "Time.h"

#include "Debug.h" // renmve after

//-----------------------------------------------------------------------------
Input* Input::Instance()
{
	static Input* input = new Input;
	return input;
}

//-----------------------------------------------------------------------------
//KeyState Input::GetKeyStates()
//{
//	return m_keyStates;
//}

//-----------------------------------------------------------------------------
glm::ivec2 Input::GetMouseMotion()
{
	return m_mouseMotion;
	
}

//-----------------------------------------------------------------------------
glm::vec2 Input::GetMousePosition()
{
	return m_mousePosition;
}

//-----------------------------------------------------------------------------
bool Input::GetMouseButtonDown(int mouseid)
{
	switch (mouseid)
	{
	case 0:
	{
		if (m_IsLeftMouseButtonPressed)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	case 1:
	{
		if (m_IsRightMouseButtonPressed)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	case 2:
	{
		if (m_IsLeftMouseButtonPressed)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	default:
		break;
	}
}

//-----------------------------------------------------------------------------
bool Input::GetMouseButtonClick(int mouseid)
{
	float currentTime = Time::GetDeltaTime();

	if (GetMouseButtonDown(mouseid))
	{
		if (!m_clicked[mouseid])
		{
			m_cooldown[mouseid] = true;
			m_startTimer[mouseid] = Time::GetDeltaTime();
		}

		m_clicked[mouseid] = true;
	}
	else
	{
		m_startTimer[mouseid] = 0;
		m_clicked[mouseid] = false;
		m_oneClick[mouseid] = false;
	}

	// 0.2f is the time of the cooldown, if it's within tht time it counts as one click
	if (currentTime - 0.2f > m_startTimer[mouseid] && m_cooldown[mouseid])
	{
		if (m_clicked[mouseid])
		{
			m_oneClick[mouseid] = false;
			m_cooldown[mouseid] = false;

		}
		else
		{
			m_oneClick[mouseid] = true;
			m_cooldown[mouseid] = false;
		}
	}
	
	if (m_oneClick[mouseid])
	{
		return true;
	}
	else
	{
		return false;
	}

}

//-----------------------------------------------------------------------------
bool Input::KeyDown(Keycode keycode)
{
	if (m_keyStates[keycode])
	{
		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------
void Input::PollEvents()
{
	SDL_Event events;

	// -------------------------------------------# Updates Key States

	m_keyStates = SDL_GetKeyboardState(nullptr);

	// -------------------------------------------# Reset Mouse Motion

	m_mouseMotion.x = 0;
	m_mouseMotion.y = 0;

	// -------------------------------------------# Polls Events

	while (SDL_PollEvent(&events))
	{
		//ImGui Events
		ImGui_ImplSDL2_ProcessEvent(&events);

		// Updates Mouse Position;
		m_mousePosition.x = events.motion.x;
		m_mousePosition.y = events.motion.y;

		switch (events.type)
		{
			case SDL_QUIT:
			{
				
				break;
			}

			case SDL_KEYDOWN:
			{
				m_IsKeyPressed = true;
				break;
			}

			case SDL_KEYUP:
			{
				m_IsKeyPressed = false;
				break;
			}

			case SDL_MOUSEMOTION:
			{
				m_mouseMotion.x = events.motion.xrel;
				m_mouseMotion.y = events.motion.yrel;

				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{
				switch (events.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						m_IsLeftMouseButtonPressed = true;
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						m_IsRightMouseButtonPressed = true;
						break;
					}

					case SDL_BUTTON_MIDDLE:
					{
						m_IsMiddleMouseButtonPressed = true;
						break;
					}


				}
				break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				switch (events.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						m_IsLeftMouseButtonPressed = false;
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						m_IsRightMouseButtonPressed = false;
						break;
					}

					case SDL_BUTTON_MIDDLE:
					{
						m_IsMiddleMouseButtonPressed = false;
						break;
					}

				}
				break;
			}
		}
	}
}
