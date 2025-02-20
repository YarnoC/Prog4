#pragma once
#include "Component.h"
#include <vector>

namespace dae
{
	class GameObject;
}

class RenderComponent : public Component
{
public:
	void Render() const;

	//there has to be a better way than this, ask alex or tom
	void LinkTexture(dae::Texture2D* texture);

	RenderComponent(dae::GameObject* ownerPtr);

	~RenderComponent() = default;
	RenderComponent(const RenderComponent&) = delete;
	RenderComponent(RenderComponent&&) = delete;
	RenderComponent& operator=(const RenderComponent&) = delete;
	RenderComponent& operator=(RenderComponent&&) = delete;

private:
	dae::Texture2D* m_LinkedTexture;
};

