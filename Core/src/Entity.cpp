#include "Entity.h"
#include <iostream>
#include "Components/Transform.h"

Entity::Entity()
{
	_components = std::vector<Component*>();
	AddComponent<Transform>();
	//_transform = GetComponent<Transform>();
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

//Transform* Entity::GetTransform()
//{
//	return _transform;
//}

