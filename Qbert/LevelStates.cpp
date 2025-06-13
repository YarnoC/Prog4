#include "LevelStates.h"
#include "LevelComponent.h"
#include "CubeComponent.h"
#include "GameTime.h"

#include <iostream>

LevelState::LevelState(LevelComponent* levelComp) :
	m_LevelComp{levelComp}
{
}

std::unique_ptr<LevelState> LevelPlayingState::CheckTiles(std::vector<std::vector<CubeComponent*>> levelTiles)
{
	for (auto&& col : levelTiles)
	{
		for (auto&& cube : col)
		{
			if (!cube->IsInCorrectState()) return nullptr;
		}
	}

	return std::make_unique<LevelFinishedState>(m_LevelComp);
}

LevelPlayingState::LevelPlayingState(LevelComponent* levelComp) :
	LevelState(levelComp)
{
	std::cout << "playingState\n";
}

std::unique_ptr<LevelState> LevelFinishedState::Update()
{
	m_TransitionTimeLeft -= dae::GameTime::GetDt();

	if (m_TransitionTimeLeft > 0) return nullptr;

	return std::make_unique<LevelPlayingState>(m_LevelComp);
}

LevelFinishedState::LevelFinishedState(LevelComponent* levelComp) :
	LevelState(levelComp)
{
	std::cout << "finishedState\n";
}
