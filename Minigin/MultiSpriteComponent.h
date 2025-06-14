#pragma once
#include "Component.h"
#include "Texture2D.h"
#include <memory>
#include "Utils.h"

namespace dae
{

class GameObject;

class MultiSpriteComponent final : public Component
{
public:
	void NextRow(bool reverse = false);
	void NextCollumn(bool reverse = false);
	void SetToRowCollumn(int row, int collumn);
	void Render() const override;
	void ResetOffset();
	void SetOffset(int x, int y);

	MultiSpriteComponent(GameObject* owner, const std::string& fileName, int rows, int collumns);
	MultiSpriteComponent(GameObject* owner, Texture2D* texture, int rows, int collumns);
	~MultiSpriteComponent() = default;

	MultiSpriteComponent(const MultiSpriteComponent&) = delete;
	MultiSpriteComponent(MultiSpriteComponent&&) = delete;
	MultiSpriteComponent& operator=(const MultiSpriteComponent&) = delete;
	MultiSpriteComponent& operator=(MultiSpriteComponent&&) = delete;
private:
	Texture2D* m_TextureSheet;
	std::unique_ptr<utils::SrcDstRect> m_SrcRect;
	glm::ivec2 m_DrawOffset{};
	int m_Rows{ 1 };
	int m_Collumns{ 1 };
	int m_CurrentRow{};
	int m_CurrentCollumn{};
};

}