#pragma once
#include "Component.h"


namespace dae
{
	class GameObject;
	class TextComponent;
}

class FpsComponent final : public dae::Component
{
public:
	void Update() override;

	FpsComponent(dae::GameObject* ownerPtr, dae::TextComponent* textComp);

	~FpsComponent() = default;
	FpsComponent(const FpsComponent& other) = delete;
	FpsComponent(FpsComponent&& other) = delete;
	FpsComponent& operator=(const FpsComponent& other) = delete;
	FpsComponent& operator=(FpsComponent&& other) = delete;

private:
	dae::TextComponent* m_TextComponentPtr;
};

