#pragma once
#include "Component.h"
#include "GameObject.h"
#include <vec2.hpp>
#include "QBertStates.h"
#include <memory>
#include "Observer.h"
#include "Component.h"

class LevelComponent;

namespace dae
{
	class MultiSpriteComponent;
}

class QBertComponent final : public dae::Component, public dae::Observer
{
public:
	void Move(glm::ivec2 moveVec);
	glm::ivec2 GetMapCoords() const;
	void SetMapCoords(glm::ivec2 newCoords);
	int GetCubeSize() const;
	glm::ivec2 GetPlayerOffset() const;
	void SetSpriteRowCol(int row, int col);
	glm::vec2 CalcPlayerPos(int row, int col) const;
	void TryChangeTile();

	void OnNotify(const dae::Event& event, Component* comp) override;

	struct Sounds
	{
		short jump;
		short fall;
		short curse;
	};

	const Sounds& GetQBertSounds() const;

	void Update() override;

	QBertComponent(dae::GameObject* owner, LevelComponent* levelComp, dae::MultiSpriteComponent* multiSpriteComp);

	~QBertComponent() = default;
	QBertComponent(const QBertComponent&) = delete;
	QBertComponent(QBertComponent&&) = delete;
	QBertComponent operator=(const QBertComponent&) = delete;
	QBertComponent operator=(QBertComponent&&) = delete;

private:
	void EnterNewState(std::unique_ptr<QbertState> newState);
	LevelComponent* m_LevelComp{ nullptr };
	dae::MultiSpriteComponent* m_SpriteComp{ nullptr };
	std::unique_ptr<QbertState> m_State{ nullptr };
	glm::ivec2 m_LevelCoords{ 7, 0 };
	glm::ivec2 m_PlayerOffset{ 16, -12 };
	Sounds m_Sounds{};
	int m_Lives{ 3 };
	
};
