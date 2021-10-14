#include "Timer.h"

void Timer::SetStart() 
{
	m_currentTime = std::chrono::steady_clock::now();
}

void Timer::SetEnd()
{
	m_lastTime = std::chrono::steady_clock::now();
}

uint64_t Timer::GetDeltaTime()
{
	return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(m_lastTime - m_currentTime).count());
}

float Timer::GetFPS()
{
	float fps = (1000000000.0f/ static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(m_lastTime - m_currentTime).count()));

	return roundf(fps);
}

bool Timer::OverTime()
{
	return m_currentTime + m_waitTime < m_lastTime;
}
