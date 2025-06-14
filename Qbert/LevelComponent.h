#pragma once
#include <vector>
#include "Texture2D.h"
#include <memory>
#include "Component.h"
#include "vec2.hpp"

namespace dae
{
class GameObject;
class Scene;
}

class CubeComponent;
class QBertComponent;
class LevelState;

class LevelComponent final : public dae::Component
{
public:
	void Update() override;

	void InitLevel(int level);
	int GetCubeSize() const;
	enum class SpawnPos
	{
		BottomLeft,
		Top,
		BottomRight
	};

	void ChangeTile(int row, int col, bool forward = true);
	int GetCurrentLevel() const;
	void SetCurrentLevel(int newLevel);

	void SetupPlayer(QBertComponent* qbertComp, SpawnPos spawnPos);
	glm::vec2 GetCubePos(int row, int col) const;

	short GetLevelCompleteSoundId() const;
	void flickerTiles();

	LevelComponent(dae::GameObject* owner, dae::Scene* scene, int level);

	~LevelComponent();

	LevelComponent(const LevelComponent&) = delete;
	LevelComponent(LevelComponent&&) = delete;
	LevelComponent& operator=(const LevelComponent&) = delete;
	LevelComponent& operator=(LevelComponent&&) = delete;

private:
	std::vector<std::vector<CubeComponent*>> m_Level;
	std::unique_ptr<LevelState> m_LevelState{ nullptr };
	const glm::ivec2 m_PlayerCubeOffset{ 16, -12 };
	dae::Texture2D* m_CubeSpriteSheet; //lifetime managed by resource manager
	int m_CubeSize{ 64 };
	int m_LevelNumber{};
	short m_LevelCompleteSoundId{};

	void EnterNewState(std::unique_ptr<LevelState> newState);
};