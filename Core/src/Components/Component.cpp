#include "Component.h"

Component::Component(Entity* entity)
{
    _entity = entity;
}

bool Component::IsEnabled()
{
    return _enabled;
}

void Component::Enabled(bool enabled)
{
    _enabled = enabled;
}
