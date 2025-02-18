#pragma once
#include <chrono>

namespace GAMETIME
{
double GetDt();
double GetFixedDt();
std::chrono::steady_clock::time_point GetCurrentClockTime();
void UpdateDt();
}    //namespace GAMETIME
