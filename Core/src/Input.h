#ifndef INPUT_H
#define INPUT_H
#include <glfw/glfw3.h>
#include <map>
#include <string>

namespace Phantom 
{

	enum KeyState {
		REALEASE = 0, PRESS = 1
	};

	struct Control
	{
		int key;
		//Event event;
		KeyState type;
	};


	class Input
	{
		public:

			Input(GLFWwindow* window);
			void UpdateKeys();
			bool GetKey(int key, KeyState state);
			bool GetMouseButton(int key, KeyState state); //GetMouseKey?

			inline static Input* Instance() { return _instance; };
			inline static void SetWindow(GLFWwindow* window) { _window = window; }

		private:
			static Input* _instance;
			static GLFWwindow* _window;
			std::map <std::string, Control> _controls;
	};
}

#endif

