#include "Timer.hpp"

float Timer::DeltaTime = 0.0F;
float Timer::timeSinceAppStart = 0.0F;
float Timer::timeSinceSceneStart = 0.0F;

void Timer::Update(float dt)
{
    Timer::DeltaTime = dt;
    Timer::timeSinceAppStart += dt;
    Timer::timeSinceSceneStart += dt;
}
