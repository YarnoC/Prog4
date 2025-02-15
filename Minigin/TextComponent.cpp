#include "TextComponent.h"
#include <SDL_ttf.h>
#include <stdexcept>
#include "Renderer.h"
#include "GameObject.h"

//using namespace dae;
using dae::Renderer;

TextComponent::TextComponent(dae::GameObject* ownerPtr, const std::string& text, dae::Font* font)
	: Renderable(ownerPtr), m_NeedsUpdate{ true }, m_Text{ text }, m_FontPtr{ font }, m_TextTextureSPtr(nullptr)
{

}

void TextComponent::Update()
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
		m_TextTextureSPtr = std::make_unique<dae::Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void TextComponent::Render() const
{
	if (m_TextTextureSPtr == nullptr) return;

	const auto& pos{ m_OwnerPtr->GetTranform().GetPosition() };
	Renderer::GetInstance().RenderTexture(*m_TextTextureSPtr, pos.x, pos.y);
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true; //dirty flag pattern
}

//void TextComponent::SetPosition(float x, float y)
//{
//	m_OwnerPtr->SetPosition(x, y);
//}