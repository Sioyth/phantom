#ifndef SCENEHIERARCHY_H
#define SCENEHIERARCHY_H
#include "../scene/Entity.h"

namespace Phantom
{
	class SceneHierarchy
	{
		public:
			static void Render();
		private:
			static void DrawLeaf(Entity* entity);
			static void DrawChildren(Entity* entity);

			static Entity* _nodeDropped;
			static Entity* _nodeSelected;
	};
}
#endif
