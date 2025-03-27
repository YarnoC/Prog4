#include "TextureComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

TextureComponent::TextureComponent(dae::GameObject* ownerPtr, const std::string& fileName)
	: Component(ownerPtr)
{
	m_TexturePtr = dae::ResourceManager::GetInstance().LoadTexture(fileName).get();
}

void TextureComponent::Render() const
{
	const auto& pos = GetOwner()->GetWorldPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_TexturePtr, pos.x, pos.y);
}

dae::Texture2D* TextureComponent::GetTexturePtr() const
{
	return m_TexturePtr;
}
