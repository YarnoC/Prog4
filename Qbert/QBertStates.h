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
	virtual std::unique_ptr<QbertState> MoveSquare(QBertComponent*, glm::ivec2) { return nullptr; };

	virtual void OnEnter() {};
	virtual void OnExit() {};

	virtual ~QbertState() = default;

	QbertState(const QbertState&) = delete;
	QbertState(QbertState&&) = delete;
	QbertState& operator=(const QbertState&) = delete;
	QbertState& operator=(QbertState&&) = delete;

protected:
	QbertState(QBertComponent* qbertComp);
	QBertComponent* m_QBertComp{ nullptr };

private:

};

class QIdleState final : public QbertState
{
public:
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
	//std::unique_ptr<QbertState> HandleState() override { return nullptr; };

	void OnExit() override;

	QJumpingState(QBertComponent* qbertComp, const glm::vec2& targetPos);

	~QJumpingState() = default;

	QJumpingState(const QJumpingState&) = delete;
	QJumpingState(QJumpingState&&) = delete;
	QJumpingState& operator=(const QJumpingState&) = delete;
	QJumpingState& operator=(QJumpingState&&) = delete;

private:
	glm::vec2 m_TargetPos{};
	glm::vec2 m_OriginalPos{};
	//glm::vec2 m_CurrentPos{};
	const static float m_JumpTime;
	short m_SoundToPlay{};
};

class QDeadState final : public QbertState
{
public:
	std::unique_ptr<QbertState> Update() override;
	void OnEnter() override;
	void OnExit() override;

	QDeadState(QBertComponent* qbertComp);

	~QDeadState() = default;

	QDeadState(const QDeadState&) = delete;
	QDeadState(QDeadState&&) = delete;
	QDeadState& operator=(const QDeadState&) = delete;
	QDeadState& operator=(QDeadState&&) = delete;

private:
	double m_DeadTimer{ 2 };
};