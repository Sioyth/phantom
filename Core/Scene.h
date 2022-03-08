#ifndef SCENE_H
#define SCENE_H
#include <entt/entt.hpp>

namespace Phantom
{
	class Scene
	{
	private:
		Scene();
		~Scene();

	public:
		entt::registry _registry;
	};
}

#endif;

