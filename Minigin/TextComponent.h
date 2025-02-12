#pragma once
#include "Component.h"
#include "Font.h"
#include "Texture2D.h"
#include <memory>
//#include <iostream>

class TextComponent final : public Component
{
public:
	void Update();
	void inline FixedUpdate() {}; //textcomponent doesn't need a fixed update

	TextComponent(const std::string& text, std::unique_ptr<dae::Font>& font);

	virtual ~TextComponent() = default;
	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;


private:
	bool m_NeedsUpdate;
	std::string m_Text;
	dae::Transform m_Transform{};
	std::unique_ptr<dae::Font> m_FontUPtr;
	std::unique_ptr<dae::Texture2D> m_TextTextureUPtr;
};
