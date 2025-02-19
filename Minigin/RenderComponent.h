#pragma once
#include "Component.h"
#include <vector>

namespace dae
{
	class GameObject;
}

class RenderComponent : Component
{
public:
	void Render() const;

	RenderComponent(dae::GameObject* ownerPtr);

	~RenderComponent() = default;
	RenderComponent(const RenderComponent&) = delete;
	RenderComponent(RenderComponent&&) = delete;
	RenderComponent& operator=(const RenderComponent&) = delete;
	RenderComponent& operator=(RenderComponent&&) = delete;

private:
	std::vector<Component*> m_RenderVec;
};

