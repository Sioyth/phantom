#ifndef WINDOW_H
#define WINDOW_H
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/vec2.hpp>

namespace Phantom
{
	class Window
	{
		public:
			bool Create();
			void SwapBuffers();
			void SetCursorMode(bool enabled);
			inline GLFWwindow& Handle() { return *_window; };
			inline bool ShouldClose() { return glfwWindowShouldClose(_window); };
			inline const glm::vec2& ViewPort() { return _viewPort; };
			~Window();
		private:
			glm::vec2 _viewPort;
			GLFWwindow* _window;
	};
}

#endif

