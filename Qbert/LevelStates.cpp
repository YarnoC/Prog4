#include "LevelStates.h"
#include "LevelComponent.h"
#include "CubeComponent.h"
#include "GameTime.h"
#include "ServiceLocator.h"

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

void LevelPlayingState::OnEnter()
{
	auto newLevel = m_LevelComp->GetCurrentLevel() + 1;
	m_LevelComp->SetCurrentLevel(newLevel);
	m_LevelComp->InitLevel(newLevel);
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

void LevelFinishedState::OnEnter()
{
	auto soundId = m_LevelComp->GetLevelCompleteSoundId();
	dae::ServiceLocator::GetSoundSystem().Play(soundId, 32, false);
}

LevelFinishedState::LevelFinishedState(LevelComponent* levelComp) :
	LevelState(levelComp)
{
	std::cout << "finishedState\n";
}
