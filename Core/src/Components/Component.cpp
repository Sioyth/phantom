#include "Component.h"

bool Component::IsEnabled()
{
    return _enabled;
}

void Component::Enabled(bool enabled)
{
    _enabled = enabled;
}
