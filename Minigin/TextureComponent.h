#pragma once
#include "Renderable.h"
#include "Texture2D.h"

class TextureComponent : public Renderable
{
public:
	void Render() const override;

	TextureComponent(dae::GameObject* ownerPtr, const std::string& fileName);

	~TextureComponent() = default;
	TextureComponent(const TextureComponent& other) = delete;
	TextureComponent(TextureComponent&& other) = delete;
	TextureComponent& operator=(const TextureComponent& other) = delete;
	TextureComponent& operator=(TextureComponent&& other) = delete;

private:
	dae::Texture2D* m_TexturePtr;
};

