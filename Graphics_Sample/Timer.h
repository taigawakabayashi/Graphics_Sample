#pragma once
#ifndef TIMER_H
#define TIMER_H
#include <chrono>

namespace Timer 
{
    uint64_t GetDeltaTIme();
    std::chrono::milliseconds GetSleepTImeForFPS(uint32_t _fps);
    void SetStart();
    void SetEnd();
    float GetFPS();
}

#endif // !TIMER_H
