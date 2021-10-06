#include "Timer.h"

namespace Timer 
{
    //-----------------------------------------------------------
    // ÉOÉçÅ[ÉoÉãïœêî
    //-----------------------------------------------------------
    std::chrono::steady_clock::
    time_point g_currentTime = std::chrono::steady_clock::now();
    
    std::chrono::steady_clock::
    time_point g_lastTime = std::chrono::steady_clock::now();
    
    uint64_t g_deltaTime = 0;
    
    
    uint64_t GetDeltaTIme()
    {
        return g_deltaTime;
    }
    
    std::chrono::milliseconds GetSleepTImeForFPS(uint32_t fps)
    {
        int64_t sleepTime = static_cast<int64_t>
                            ((1000000000 / fps) - g_deltaTime) / 1000000;
    
        if (sleepTime < 0)
        {
            sleepTime = 1;
        }
    
        return std::chrono::milliseconds(sleepTime);
    }
    
    void SetStart()
    {
        g_currentTime = std::chrono::steady_clock::now();
    
        g_deltaTime = std::chrono::duration_cast
                      <std::chrono::microseconds>
                      (g_currentTime - g_lastTime).count();
    }
    
    void SetEnd()
    {
        g_lastTime = g_currentTime;
    }
    
    float GetFPS()
    {
        float fps = (1000000.0f / g_deltaTime);
    
        return fps;
    }
}
