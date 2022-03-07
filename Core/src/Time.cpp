#include "Time.h"

float Time::_deltaTime = 0;

void Time::UpdateDeltaTime(float currentTime)
{
    static float lastFrame = 0.0f;
    float currentFrame = currentTime;
    _deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
