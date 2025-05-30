#include "TextComponent.h"
#include <SDL_ttf.h>
#include <stdexcept>
#include "Renderer.h"
#include "GameObject.h"

//using namespace dae;
using dae::Renderer;

dae::TextComponent::TextComponent(dae::GameObject* ownerPtr, const std::string& text, dae::Font* font)
	: Component(ownerPtr), m_NeedsUpdate{ true }, m_Text{ text }, m_FontPtr{ font }, m_TextTextureUPtr(nullptr)
{
	UpdateText();
}

void dae::TextComponent::UpdateText()
{
	if (m_NeedsUpdate)
	{
		//TODO: add ability to change text color
		const SDL_Color color = { 255, 255, 255, 255 }; //only supports white text atm
		const auto surf = TTF_RenderText_Blended(m_FontPtr->GetFont(), m_Text.c_str(), color); //surface

		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}

		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);

		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}

		SDL_FreeSurface(surf);
		m_TextTextureUPtr = std::make_unique<dae::Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Update()
{
	UpdateText();
}

void dae::TextComponent::Render() const
{
	const auto& pos = GetOwner()->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_TextTextureUPtr, pos.x, pos.y);
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true; //dirty flag pattern
}