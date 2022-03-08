#include "Scene.h"

namespace Phantom
{
	Scene::Scene()
	{
		entt::entity entity = _registry.create();
	}

	Scene::~Scene()
	{

	}
}
