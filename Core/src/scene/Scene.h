#ifndef SCENE_H
#define SCENE_H
#include <entt/entt.hpp>
#include "EditorCamera.h"
namespace Phantom
{
	class Entity;

	class Scene
	{
		public:
			Scene();
			~Scene();

			void Update(const float& dt);
			Entity* activeCamera();
			Entity& CreateEntity(const std::string& name = "");

		private:
			Entity* _activeCamera;
			entt::registry _registry;
			EditorCamera _editorCamera;
			std::vector<Entity> _entities;

			friend class Entity;
			friend class Renderer;
	};
}

#endif;

