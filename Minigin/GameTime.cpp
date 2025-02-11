#include "GameTime.h"
#include <chrono>

using namespace GAMETIME;

double g_Dt = 0.0;
double g_FixedDt = 1 / 60.0;
std::chrono::steady_clock::time_point g_LastTime = std::chrono::high_resolution_clock::now();

[[nodiscard]] double GAMETIME::GetDt()
{
    return g_Dt;
}

[[nodiscard]] double GAMETIME::GetFixedDt()
{
    return g_FixedDt;
}

//only to be used in the main loop
void GAMETIME::UpdateDt()
{
    const auto currentTime{ std::chrono::high_resolution_clock::now() };
    const auto frameDuration{ std::chrono::duration<double>(currentTime - g_LastTime).count() };
    g_Dt = std::min(frameDuration, 1.0); //prevent death spiral
    g_LastTime = currentTime;
}
