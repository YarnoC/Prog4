#include "GameTime.h"
#include <algorithm>

double GameTime::m_Dt = 0.0;
std::chrono::high_resolution_clock::time_point GameTime::m_LastTime = std::chrono::high_resolution_clock::now();
std::chrono::high_resolution_clock::time_point GameTime::m_CurrentTime = std::chrono::high_resolution_clock::now();

[[nodiscard]] double GameTime::GetDt()
{
    return m_Dt;
}

[[nodiscard]] double GameTime::GetFixedDt()
{
    return m_FixedDt;
}

std::chrono::steady_clock::time_point GameTime::GetCurrentClockTime()
{
    return m_CurrentTime;
}

//only to be used in the main loop
void GameTime::UpdateDt()
{
    m_CurrentTime = std::chrono::high_resolution_clock::now();
    const auto frameDuration{ std::chrono::duration<double>(m_CurrentTime - m_LastTime).count() };
    m_Dt = std::min(frameDuration, 1.0); //prevent death spiral
    m_LastTime = m_CurrentTime;
}
