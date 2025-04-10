#pragma once
#include "Component.h"
#include "Font.h"
#include "Texture2D.h"
#include <memory>

namespace dae
{

class TextComponent final : public Component
{
public:
	void Update();
	void Render() const override;
	dae::Texture2D* GetTexturePtr() const override;

	void SetText(const std::string& text);

	TextComponent(dae::GameObject* ownerPtr, const std::string& text, dae::Font* font);

	virtual ~TextComponent() = default;
	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;


private:
	bool m_NeedsUpdate;
	std::string m_Text;
	dae::Font* m_FontPtr;
	std::unique_ptr<dae::Texture2D> m_TextTextureUPtr;

	void UpdateText();
};

}