#ifndef SCENE_H
#define SCENE_H
#include <entt/entt.hpp>
#include "EditorCamera.h"
#include "Entity.h"
namespace Phantom
{
	class Scene
	{
		public:
			Scene();
			~Scene();

			void Update(const float& dt);
			Entity* activeCamera();
			std::unique_ptr<Entity>* CreateEntity(const std::string& name = "Empty Entity");
			inline std::vector<std::unique_ptr<Entity>>& Entities() { return _entities; };

		private:
			Entity* _activeCamera;
			entt::registry _registry;
			EditorCamera _editorCamera;
			std::vector<std::unique_ptr<Entity>> _entities;

			friend class Entity;
			friend class Renderer;
	};
}

#endif;

