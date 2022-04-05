#ifndef SCENE_H
#define SCENE_H
#include <entt/entt.hpp>
#include "../editor/EditorCamera.h"
#include "Entity.h"
namespace Phantom
{
	class Scene
	{
		public:
			Scene(bool stock = false);
			~Scene();

			void Update(const float& dt);
			Entity* activeCamera();
			std::unique_ptr<Entity>* CreateEntity(const std::string& name = "Empty Entity");
			inline std::vector<std::unique_ptr<Entity>>& Entities() { return _entities; };

		private:
			Entity* _activeCamera;
			entt::registry _registry;
			std::vector<std::unique_ptr<Entity>> _entities;

			friend class Entity;
			friend class Renderer;
	};
}

#endif;

