#pragma once
#include <vec2.hpp>
#include <memory>
#include <vec3.hpp>

class LevelComponent;
class QBertComponent;

class QbertState
{
public:
	virtual std::unique_ptr<QbertState> Update() { return nullptr; };
	virtual std::unique_ptr<QbertState> HandleState() = 0;
	virtual std::unique_ptr<QbertState> MoveSquare(QBertComponent*, glm::ivec2) { return nullptr; };

	virtual void OnEnter(QBertComponent*) {};
	virtual void OnExit(QBertComponent*) {};

	virtual ~QbertState() = default;

	QbertState(const QbertState&) = delete;
	QbertState(QbertState&&) = delete;
	QbertState& operator=(const QbertState&) = delete;
	QbertState& operator=(QbertState&&) = delete;

protected:
	//maybe get ref to player here?
	QbertState(QBertComponent* qbertComp);
	QBertComponent* m_QBertComp{ nullptr };


private:

};

class QIdleState final : public QbertState
{
public:
	//void Update() override;
	std::unique_ptr<QbertState> HandleState() override;
	std::unique_ptr<QbertState> MoveSquare(QBertComponent* qbertComp, glm::ivec2 moveVec);

	QIdleState(QBertComponent* qbertComp);
	~QIdleState() = default;

	QIdleState(const QIdleState&) = delete;
	QIdleState(QIdleState&&) = delete;
	QIdleState& operator=(const QIdleState&) = delete;
	QIdleState& operator=(QIdleState&&) = delete;
private:

};

class QJumpingState final : public QbertState
{
public:
	std::unique_ptr<QbertState> Update() override;
	std::unique_ptr<QbertState> HandleState() override { return nullptr; };

	QJumpingState(QBertComponent* qbertComp, const glm::vec3& targetPos);

	~QJumpingState() = default;

	QJumpingState(const QJumpingState&) = delete;
	QJumpingState(QJumpingState&&) = delete;
	QJumpingState operator=(const QJumpingState&) = delete;
	QJumpingState operator=(QJumpingState&&) = delete;

private:
	glm::vec3 m_TargetPos{};
	glm::vec3 m_OrignalPos{};
	float m_Distance{};
	const static float m_JumpTime;
};