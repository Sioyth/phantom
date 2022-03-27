#ifndef APPLICATION_H
#define APPLICATION_H

#include <glad/glad.h>
#include "Phantom.h"

namespace Phantom
{
	class Application
	{
		public:
			Application();
			~Application();
			void Quit();
			
		private:
			void Run();
			void Start();
			void LoadGlad();
			Window _window;
	};
}
#endif 