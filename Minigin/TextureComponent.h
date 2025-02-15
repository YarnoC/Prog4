#pragma once
#include "Renderable.h"
#include "Texture2D.h"

class TextureComponent : public Renderable
{
public:
	TextureComponent(dae::GameObject* ownerPtr, const std::string& fileName);
	void Render() const override;
private:
	dae::Texture2D* m_TexturePtr;
};

