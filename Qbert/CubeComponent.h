#pragma once
#include "MultiSpriteComponent.h"

namespace dae
{
class GameObject;
}

class CubeComponent final : public dae::Component
{
public:
	void OnLandOn();
	void SetToLevel(int level);

	CubeComponent(dae::GameObject* owner, dae::MultiSpriteComponent* spriteComp, int level);
	~CubeComponent() = default;

	CubeComponent(const CubeComponent&) = delete;
	CubeComponent(CubeComponent&&) = delete;
	CubeComponent& operator=(const CubeComponent&) = delete;
	CubeComponent& operator=(CubeComponent&) = delete;
private:
	dae::MultiSpriteComponent* m_Sprite;
	int m_Level{};
	int m_Stage{};
};

