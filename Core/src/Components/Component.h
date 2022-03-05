#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include "../Entity.h"

class Entity;

class Component
{
	public:
		Component(Entity* entity);
		bool IsEnabled() { return _isEnabled; };
		void Enabled(bool enabled) { _isEnabled = enabled; }; // rename enabled - Condition? State? flag?

		Entity* GetEntity() { return _entity; };
		//virtual void Start() = 0;
		virtual void Update() = 0;

	protected:
		bool _isEnabled;
		Entity* _entity;
		std::string _name;
};

#endif 

