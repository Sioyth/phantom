#include "Component.h"

Component::Component(Entity* entity)
{
    _entity = entity;
    _isEnabled = true;
    _name = typeid(this).name();
    //Start
}

