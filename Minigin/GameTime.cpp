#include "GameTime.h"
#include <algorithm>

double dae::GameTime::m_Dt = 0.0;
std::chrono::high_resolution_clock::time_point dae::GameTime::m_LastTime = std::chrono::high_resolution_clock::now();
std::chrono::high_resolution_clock::time_point dae::GameTime::m_CurrentTime = std::chrono::high_resolution_clock::now();

[[nodiscard]] double dae::GameTime::GetDt()
{
    return m_Dt;
}

[[nodiscard]] double dae::GameTime::GetFixedDt()
{
    return m_FixedDt;
}

std::chrono::steady_clock::time_point dae::GameTime::GetCurrentClockTime()
{
    return m_CurrentTime;
}

//only to be used in the main loop
void dae::GameTime::UpdateDt()
{
    m_CurrentTime = std::chrono::high_resolution_clock::now();
    const auto frameDuration{ std::chrono::duration<double>(m_CurrentTime - m_LastTime).count() };
    m_Dt = std::min(frameDuration, 1.0); //prevent death spiral
    m_LastTime = m_CurrentTime;
}
