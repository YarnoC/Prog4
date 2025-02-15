#include "TextureComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

TextureComponent::TextureComponent(dae::GameObject* ownerPtr, const std::string& fileName)
	: Renderable(ownerPtr)
{
	m_TexturePtr = dae::ResourceManager::GetInstance().LoadTexture(fileName).get();
}

void TextureComponent::Render() const
{
	//const auto& pos = m_OwnerPtr->GetTranform().GetPosition();
	//dae::Renderer::GetInstance().RenderTexture(*m_TexturePtr, pos.x, pos.y);
}
