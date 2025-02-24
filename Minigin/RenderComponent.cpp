#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"

void RenderComponent::Render() const
{
	if (m_LinkedTexture == nullptr) return; //HACK: ask about optimizing the linking

	const auto& pos = GetOwner()->GetWorldPosition();

	//this line severely breaks when the texture for the font gets remade as it's a UPtr which gets remade in a diff place, need to fix
	//maybe give the rendercomp's texturePtr to the other components so they can update their textures straight into the rendercomp's ptr, as that one shouldn't change
	dae::Renderer::GetInstance().RenderTexture(*m_LinkedTexture, pos.x, pos.y);
}

void RenderComponent::LinkTexture(dae::Texture2D* texture)
{
	m_LinkedTexture = texture;
}

RenderComponent::RenderComponent(dae::GameObject* ownerPtr) : Component(ownerPtr), m_LinkedTexture{nullptr}
{
}