#pragma once
#include "Component.h"
#include "GameObject.h"
#include <vec2.hpp>
#include "QBertStates.h"
#include <memory>

class LevelComponent;

class QBertComponent final : public dae::Component
{
public:
	void Move(glm::ivec2 moveVec);
	glm::ivec2 GetMapCoords() const;
	void SetMapCoords(glm::ivec2 newCoords);
	int GetCubeSize() const;

	QBertComponent(dae::GameObject* owner, LevelComponent* levelComp);

	~QBertComponent() = default;
	QBertComponent(const QBertComponent&) = delete;
	QBertComponent(QBertComponent&&) = delete;
	QBertComponent operator=(const QBertComponent&) = delete;
	QBertComponent operator=(QBertComponent&&) = delete;

private:
	LevelComponent* m_LevelComp{ nullptr };
	std::unique_ptr<QbertState> m_State{ nullptr };
	glm::ivec2 m_LevelCoords{ 7, 0 };
	int m_Lives{ 3 };
};
