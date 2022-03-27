#ifndef UI_H
#define UI_H
#include <glfw/glfw3.h>

namespace Phantom
{
	class UI
	{
		public:
			static void NewFrame();
			static void EndFrame();
			static void ShutDown();
			static bool Init(GLFWwindow& window);
	};
}

#endif

