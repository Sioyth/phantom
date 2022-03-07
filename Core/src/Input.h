#ifndef INPUT_H
#define INPUT_H
#include <glfw/glfw3.h>
#include <map>
#include <string>

enum class KeyState {
	REALEASE = 0, PRESS
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
		bool GetMouseButton(); //GetMouseKey?

		inline static Input* Instance() { return _instance; };

	private:
		static Input* _instance;
		static GLFWwindow* _window;
		std::map <std::string, Control> _controls;
};

#endif
