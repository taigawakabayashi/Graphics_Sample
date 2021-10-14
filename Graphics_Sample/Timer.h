#pragma once
#ifndef TIMER_H
#define TIMER_H
#include <chrono>

class Timer 
{
public:

	Timer(uint64_t _fps) 
	{
		m_waitTime = std::chrono::nanoseconds(1000000000 / _fps);
	}

	void SetStart();
	void SetEnd();

	uint64_t GetDeltaTime();
	float GetFPS();

	bool OverTime();

private:

	std::chrono::steady_clock::
		time_point m_currentTime = std::chrono::steady_clock::now();

	std::chrono::steady_clock::
		time_point m_lastTime = std::chrono::steady_clock::now();

	std::chrono::nanoseconds m_waitTime = std::chrono::nanoseconds(0);
};

#endif // !TIMER_H
