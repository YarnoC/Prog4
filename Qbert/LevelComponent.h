#pragma once
#include <vector>
#include "Texture2D.h"
#include <memory>
#include "Component.h"

namespace dae
{
class GameObject;
class Scene;
}

class CubeComponent;
class QBertComponent;

class LevelComponent final : public dae::Component
{
public:
	void InitLevel(int level);
	int GetCubeSize() const;
	//enum class SpawnPos
	//{
	//	BottomLeft,
	//	Top,
	//	BottomRight
	//};

	//void SetupPlayer(QBertComponent* qbert, SpawnPos spawnPos);
	//void Move(QBertComponent* qbertComp, glm::ivec2 moveVec);

	LevelComponent(dae::GameObject* owner, dae::Scene* scene, int level);

	~LevelComponent() = default;

	LevelComponent(const LevelComponent&) = delete;
	LevelComponent(LevelComponent&&) = delete;
	LevelComponent& operator=(const LevelComponent&) = delete;
	LevelComponent& operator=(LevelComponent&&) = delete;

private:
	const glm::ivec2 m_PlayerCubeOffset{ 16, -12 };
	std::vector<std::vector<CubeComponent*>> m_Level;
	dae::Texture2D* m_CubeSpriteSheet; //lifetime managed by resource manager
	int m_CubeSize{ 64 };
};