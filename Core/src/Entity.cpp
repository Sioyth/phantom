#include "Entity.h"
#include <iostream>

namespace Phantom {

	Entity::Entity(entt::entity id, Scene* scene)
	{
		_id = id;
		_scene = scene;
	}
}
