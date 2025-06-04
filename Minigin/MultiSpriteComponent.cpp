#include "MultiSpriteComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

void dae::MultiSpriteComponent::NextRow(bool reverse)
{
	m_CurrentRow = (m_Rows + m_CurrentRow + (1 + -2 * reverse)) % m_Rows;
	m_SrcRect->y = m_CurrentRow * m_SrcRect->height;
}

void dae::MultiSpriteComponent::NextCollumn(bool reverse)
{
	m_CurrentCollumn = (m_Collumns + m_CurrentCollumn + (1 + -2 * reverse)) % m_Collumns;
	m_SrcRect->x = m_CurrentCollumn * m_SrcRect->width;
}

void dae::MultiSpriteComponent::Render() const
{
	const auto& pos = GetOwner()->GetWorldPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_TextureSheet, pos.x, pos.y, *m_SrcRect);
}

dae::MultiSpriteComponent::MultiSpriteComponent(GameObject* owner, const std::string& fileName, int rows, int collumns) :
	Component(owner), m_Rows {rows}, m_Collumns{ collumns }
{
	m_TextureSheet = dae::ResourceManager::GetInstance().LoadTexture(fileName).get();
	m_SrcRect = std::make_unique<utils::SrcDstRect>();
	m_SrcRect->width = static_cast<int>(m_TextureSheet->GetSize().x / collumns);
	m_SrcRect->height = static_cast<int>(m_TextureSheet->GetSize().y / rows);
}

dae::MultiSpriteComponent::MultiSpriteComponent(GameObject* owner, Texture2D* texture, int rows, int collumns) :
	Component(owner), m_TextureSheet{texture}, m_Rows{rows}, m_Collumns{collumns}
{
	m_SrcRect = std::make_unique<utils::SrcDstRect>();
	m_SrcRect->width = static_cast<int>(m_TextureSheet->GetSize().x / collumns);
	m_SrcRect->height = static_cast<int>(m_TextureSheet->GetSize().y / rows);
}
