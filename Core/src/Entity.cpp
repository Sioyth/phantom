#include "Entity.h"
#include "Components/Transform.h"
#include <iostream>

Entity::Entity()
{
	_components = std::vector<Component*>();
	AddComponent<Transform>();
}

bool Entity::IsEnabled()
{
	return _enabled;
}

void Entity::Enabled(bool enabled)
{
	_enabled = _enabled;
}

void Entity::Update()
{
	for (int i = 0; i < _components.size(); i++)
	{
		if (_components[i]->IsEnabled())
			_components[i]->Update();
	}
}

