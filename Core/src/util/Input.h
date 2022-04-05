#ifndef INPUT_H
#define INPUT_H
#include <glfw/glfw3.h>
#include <glm/vec2.hpp>
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

			void PollEvents();
			void UpdateKeys();
			bool GetKey(int key, KeyState state);

			const glm::vec2 &GetMousePos();
			bool GetMouseButton(int key, KeyState state); //GetMouseKey?

			static Input* Instance();

		private:
			static Input* _instance;
			static GLFWwindow* _window;
			std::map <std::string, Control> _controls;
			inline static void SetWindow(GLFWwindow& window) { _window = &window; }

			friend class Application;
	};
}

#endif

