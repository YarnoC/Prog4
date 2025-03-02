#pragma once
#include <array>
#include <vector>
#include <chrono>
#include <cmath>

class GameObject3D;
class GameObject3DAlt;

class CacheBenchmark final
{
public:
	void TimeInts();
	void TimeGo();
	void TimeGoa();

	CacheBenchmark();

	~CacheBenchmark();
	CacheBenchmark(const CacheBenchmark&) = delete;
	CacheBenchmark(CacheBenchmark&&) = delete;
	CacheBenchmark& operator=(const CacheBenchmark&) = delete;
	CacheBenchmark& operator=(CacheBenchmark&&) = delete;
private:
	size_t m_ArrSize{ static_cast<size_t>(std::pow(2, 26)) };
	std::array<long long, 11> m_IntTimings;
	std::array<long long, 11> m_GameObjTimings;
	std::array<long long, 11> m_GameObjAltTimings;
	
	int* m_IntArr;
	GameObject3D* m_GoArr;
	GameObject3DAlt* m_GoaArr;
};

