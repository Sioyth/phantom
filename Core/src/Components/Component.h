#ifndef COMPONENT_H
#define COMPONENT_H

#include "../Entity.h"

#include <iostream>

class Entity;
class Component
{
	public:
		Component(Entity* entity);
		bool IsEnabled();
		void Enabled(bool enabled);

		//virtual void Start() = 0;
		virtual void Update() = 0;

	private:
		Entity* _entity;
		bool _enabled;
};

#endif 

