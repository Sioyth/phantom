#include "Entity.h"
#include <iostream>

namespace Phantom {

	Entity::Entity(entt::entity id, Scene* scene)
	{
		_id = id;
		_scene = scene;

		//Add and store transform (bug why can't I pass it as reference?)
		//entity.SetTransform(&entity.AddComponent<Transform>());

		_transform = &AddComponent<Transform>();

		//// Tag
		//Tag& tag = entity.AddComponent<Tag>();
		//tag._name = name.empty() ? "Entity" : name;
	}
	Transform* Entity::transform()
	{
		return _transform;
	}
	void Entity::SetTransform(Transform* transform)
	{
		_transform = transform;
	}
}
