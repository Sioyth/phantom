#ifndef UI_H
#define UI_H
//temp
#include "render/Renderer.h"

namespace Phantom
{
	class Entity;
	class UI
	{
		public:

			static void Render();
			static void ShutDown();
			static bool Init(GLFWwindow* window);

			static void NewFrame();
			static void EndFrame();
		private:

			static void DrawChildren(Entity* entity);
			static void DrawLeaf(Entity* entity);
			static Entity* _nodeSelected;

			// Temp
			static glm::vec2 currentViewPortSize; 
			static Entity* _nodeDropped;
	};
}

#endif

