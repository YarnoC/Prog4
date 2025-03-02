#include "CacheBenchmark.h"
#include "CacheBenchmark.h"
#include <iostream>

struct Transform
{
	float matrix[16]
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
};

class GameObject3D
{
public:
	Transform transform;
	int Id{};
};

class GameObject3DAlt
{
public:
	Transform* transformPtr;
	int Id{};
};

void CacheBenchmark::TimeInts()
{
	int j{};
	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		auto begin = std::chrono::high_resolution_clock::now();

		for (int i{}; i < m_ArrSize; i += stepsize)
		{
			m_IntArr[i] *= 2;
		}

		auto end = std::chrono::high_resolution_clock::now();
		m_IntTimings[j] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
		++j;
	}

	std::cout << "Int timings:\n";
	for (auto&& time : m_IntTimings)
	{
		std::cout << time << std::endl;
	}
	std::cout << std::endl;
}

void CacheBenchmark::TimeGo()
{
	int j{};
	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		auto begin = std::chrono::high_resolution_clock::now();

		for (int i{}; i < m_ArrSize; i += stepsize)
		{
			m_GoArr[i].Id *= 2;
		}

		auto end = std::chrono::high_resolution_clock::now();
		m_GameObjTimings[j] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
		++j;
	}

	std::cout << "GameObject3D timings:\n";
	for (auto&& time : m_GameObjTimings)
	{
		std::cout << time << std::endl;
	}
	std::cout << std::endl;
}

void CacheBenchmark::TimeGoa()
{
	int j{};
	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		auto begin = std::chrono::high_resolution_clock::now();

		for (int i{}; i < m_ArrSize; i += stepsize)
		{
			m_GoaArr[i].Id *= 2;
		}

		auto end = std::chrono::high_resolution_clock::now();
		m_GameObjAltTimings[j] = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
		++j;
	}

	std::cout << "GameObject3DAlt timings:\n";
	for (auto&& time : m_GameObjAltTimings)
	{
		std::cout << time << std::endl;
	}
	std::cout << std::endl;
}

CacheBenchmark::CacheBenchmark()
{
	m_IntArr = new int[m_ArrSize]{};
	m_GoArr = new GameObject3D[m_ArrSize]{};
	m_GoaArr = new GameObject3DAlt[m_ArrSize]{};
}

CacheBenchmark::~CacheBenchmark()
{
	delete[] m_IntArr;
	delete[] m_GoArr;
	delete[] m_GoaArr;
}
