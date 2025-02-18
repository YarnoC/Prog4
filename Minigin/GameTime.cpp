#include "GameTime.h"
#include <algorithm>

using namespace GAMETIME;

double g_Dt = 0.0;
double g_FixedDt = 1 / 60.0;
auto g_LastTime = std::chrono::high_resolution_clock::now();
auto g_CurrentTime = std::chrono::high_resolution_clock::now();

[[nodiscard]] double GAMETIME::GetDt()
{
    return g_Dt;
}

[[nodiscard]] double GAMETIME::GetFixedDt()
{
    return g_FixedDt;
}

std::chrono::steady_clock::time_point GAMETIME::GetCurrentClockTime()
{
    return g_CurrentTime;
}

//only to be used in the main loop
void GAMETIME::UpdateDt()
{
    g_CurrentTime = std::chrono::high_resolution_clock::now();
    const auto frameDuration{ std::chrono::duration<double>(g_CurrentTime - g_LastTime).count() };
    g_Dt = std::min(frameDuration, 1.0); //prevent death spiral
    g_LastTime = g_CurrentTime;
}
