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

			// TEMP - Should be handled through some sort of SCENE MANAGER instead.
			Entity* activeCamera();
			Entity CreateEntity(const std::string& name = std::string());

			/*Scene(const Scene& other) {
				_registry = other._registry;
			};*/

		private:
			EditorCamera _editorCamera;
			Entity* _activeCamera;
			entt::registry _registry;
			friend class Entity;
			friend class Renderer;
	};
}

#endif;

