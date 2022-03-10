#ifndef SCENE_H
#define SCENE_H
#include <entt/entt.hpp>
#include "components/Components.h"

namespace Phantom
{

	class Entity;

	class Scene
	{
		public:
			Scene();
			~Scene();

			void Update();

			// TEMP - Should be handled through some sort of SCENE MANAGER instead.
			Entity CreateEntity(const std::string& name = std::string());

		private:
			entt::registry _registry;
			friend class Entity;
	};
}

#endif;

