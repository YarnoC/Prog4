#pragma once
#include "Component.h"

class TextComponent;

namespace dae
{

class GameObject;
}
class FpsComponent final : public Component
{
public:
	void Update() override;

	FpsComponent(dae::GameObject* ownerPtr, TextComponent* textComp);

	~FpsComponent() = default;
	FpsComponent(const FpsComponent& other) = delete;
	FpsComponent(FpsComponent&& other) = delete;
	FpsComponent& operator=(const FpsComponent& other) = delete;
	FpsComponent& operator=(FpsComponent&& other) = delete;

private:
	TextComponent* m_TextComponentPtr;
};

