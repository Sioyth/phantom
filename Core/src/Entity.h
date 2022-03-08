#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include "Components/Component.h"
class Component;

class Entity
{
public:
	Entity();

	bool IsEnabled();
	void Enabled(bool enabled);
	void Update();

	inline const void Name(std::string name) { _name = name; };
	inline const std::string& Name() { return _name; };

	template<class T> void AddComponent();
	template<class T> T* GetComponent();
	void RemoveComponent();

	private:
		bool _enabled;
		unsigned int _id;
		std::string _name;
		//Transform* _transform;
		std::vector<Component*> _components;
};


template<class T>
inline void Entity::AddComponent()
{
	_components.push_back(new T(this));
}

template<class T>
inline T* Entity::GetComponent()
{
	for (int i = 0; i < _components.size(); i++)
	{
		T* t = dynamic_cast<T*>(_components[i]);
		if (t != nullptr)
			return t;
	}

	return nullptr;
}

#endif;


