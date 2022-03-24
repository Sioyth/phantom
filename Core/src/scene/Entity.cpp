#include "Entity.h"
#include <iostream>

namespace Phantom {

	Entity::Entity(entt::registry& registry, std::string name)
	{
		_name = name;
		_registry = &registry;
		_id = _registry->create();

		// TODO: BETTER WAY TO DO THIS
		_parent = nullptr;
		_transform = &AddComponent<Transform>();
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
		std::cout << "Deleted " + _name << std::endl;
		//delete _parent;
		// Loop through vector of pointers, delete each pointer then clear. Otherwise it will have a memory leak
		/*for (int i = 0; i < _children.size(); i++)
		{
			delete _children[i];
		}*/

		_children.clear();
	}
	void Entity::AddChild(Entity* child)
	{
		std::cout << "Child: " << child->Name() << std::endl;
		_children.push_back(child);

	}
	void Entity::SetParent(Entity* parent)
	{
		//parent->AddChild(this);
		_parent = parent;
		//parent.get.add
		std::cout << "Parent: " << _parent->Name() << std::endl;
	}
	void Entity::RemoveChild(Entity* child)
	{
		auto it = std::find(_children.begin(), _children.end(), child);
		if(it != _children.end())
			_children.erase(it);
	}
}
