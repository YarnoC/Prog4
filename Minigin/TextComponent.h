#pragma once
//#include "Component.h"
#include "Font.h"
#include "Texture2D.h"
#include <memory>
//#include <iostream>
#include "Renderable.h"

class TextComponent final : public Renderable
{
public:
	void Update();
	void Render() const override;

	void SetText(const std::string& text);
	//void SetPosition(float x, float y);

	TextComponent(dae::GameObject* ownerPtr, const std::string& text, dae::Font* font);

	virtual ~TextComponent() = default;
	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;


private:
	bool m_NeedsUpdate;
	std::string m_Text;
	//dae::Transform m_Transform{}; //move whole gameobect instead
	dae::Font* m_FontPtr;
	std::shared_ptr<dae::Texture2D> m_TextTextureSPtr; //TODO: probably change this to a raw pointer as well
};
