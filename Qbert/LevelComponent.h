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

class LevelComponent final : public dae::Component
{
public:
	void InitLevel(int level);
	LevelComponent(dae::GameObject* owner, dae::Scene& scene, int level);

	~LevelComponent() = default;

	LevelComponent(const LevelComponent&) = delete;
	LevelComponent(LevelComponent&&) = delete;
	LevelComponent& operator=(const LevelComponent&) = delete;
	LevelComponent& operator=(LevelComponent&&) = delete;

private:
	std::vector<std::vector<CubeComponent*>> m_Level;
	std::unique_ptr<dae::Texture2D> m_CubeSpriteSheet;
};