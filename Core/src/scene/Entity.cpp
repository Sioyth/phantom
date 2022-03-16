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

	Entity::~Entity()
	{
		delete _parent;
		// Loop through vector of pointers, delete each pointer then clear. Otherwise it will have a memory leak
		for (int i = 0; i < _children.size(); i++)
		{
			delete _children[i];
		}

		_children.clear();
	}
	void Entity::AddChild(Entity& child)
	{
		_children.push_back(&child);
	}
	void Entity::SetParent(Entity& parent)
	{
		_parent = &parent;
	}
}
