#ifndef APPLICATION_H
#define APPLICATION_H

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
			Window _window;
	};
}
#endif 