#include "TextureComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

dae::TextureComponent::TextureComponent(dae::GameObject* ownerPtr, const std::string& fileName)
	: Component(ownerPtr)
{
	m_TexturePtr = dae::ResourceManager::GetInstance().LoadTexture(fileName).get();
}

void dae::TextureComponent::Render() const
{
	const auto& pos = GetOwner()->GetWorldPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_TexturePtr, pos.x, pos.y);
}
