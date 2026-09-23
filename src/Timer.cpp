#include "Timer.h"

Timer::Timer() : m_time(0.0f) {}
void Timer::Update(float dt) { m_time += dt; }
void Timer::Restart() { m_time = 0.0f; }
float Timer::Get() const { return m_time; }
