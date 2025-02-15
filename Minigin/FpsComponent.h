#pragma once
#include "Component.h"

namespace dae
{

class GameObject;
}
class FpsComponent : public Component
{
public:
	void Update() override;

	FpsComponent(dae::GameObject* ownerPtr);

	~FpsComponent() = default;
	FpsComponent(const FpsComponent& other) = delete;
	FpsComponent(FpsComponent&& other) = delete;
	FpsComponent& operator=(const FpsComponent& other) = delete;
	FpsComponent& operator=(FpsComponent&& other) = delete;
};

