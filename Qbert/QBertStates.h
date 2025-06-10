#pragma once
#include <vec2.hpp>
#include <memory>

class QbertState
{
public:
	virtual void Update() {};
	virtual std::unique_ptr<QbertState> HandleState() = 0;
	virtual std::unique_ptr<QbertState> MoveSquare(glm::ivec2) { return nullptr; };

	virtual void OnEnter() {};
	virtual void OnExit() {};

	virtual ~QbertState() = default;

	QbertState(const QbertState&) = delete;
	QbertState(QbertState&&) = delete;
	QbertState& operator=(const QbertState&) = delete;
	QbertState& operator=(QbertState&&) = delete;

protected:
	//maybe get ref to player here?
	QbertState() = default;

private:

};

class QIdleState final : public QbertState
{
public:
	//void Update() override;
	std::unique_ptr<QbertState> HandleState() override;
	//also needs a ref to the player
	std::unique_ptr<QbertState> MoveSquare(glm::ivec2 moveVec);

	QIdleState();
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

private:

};