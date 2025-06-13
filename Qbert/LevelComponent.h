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

	void SetupPlayer(QBertComponent* qbertComp, SpawnPos spawnPos);
	//void Move(QBertComponent* qbertComp, glm::ivec2 moveVec);
	glm::vec2 GetCubePos(int row, int col) const;

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
};