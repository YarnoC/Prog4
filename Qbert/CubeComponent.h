#pragma once
#include "MultiSpriteComponent.h"

namespace dae
{

class GameObject;

class CubeComponent final : public Component
{
public:
	void NextStage();

	CubeComponent(GameObject*, MultiSpriteComponent* spriteComp, int level);
	~CubeComponent() = default;

	CubeComponent(const CubeComponent&) = delete;
	CubeComponent(CubeComponent&&) = delete;
	CubeComponent& operator=(const CubeComponent&) = delete;
	CubeComponent& operator=(CubeComponent&) = delete;
private:
	MultiSpriteComponent* m_Sprite;
	int m_Level{};
	int m_Stage{};
};

}