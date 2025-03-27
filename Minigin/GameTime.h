#pragma once
#include <chrono>

class GameTime
{
public:
	static double GetDt();
	static double GetFixedDt();
	static std::chrono::steady_clock::time_point GetCurrentClockTime();
	static void UpdateDt();
private:
	static double m_Dt;
	constexpr static double m_FixedDt{ 1 / 60.0 };
	static std::chrono::high_resolution_clock::time_point m_LastTime;
	static std::chrono::high_resolution_clock::time_point m_CurrentTime;
};
