#pragma once
#include "Command.h"
#include "vec2.hpp"

class QBertComponent;

class MoveActorCommand final : public dae::GameActorCommand
{
public:
	MoveActorCommand(dae::GameObject* actor, glm::vec2 moveVec);
	void Execute();

	~MoveActorCommand() = default;

	MoveActorCommand(const MoveActorCommand&) = delete;
	MoveActorCommand(MoveActorCommand&&) = delete;
	MoveActorCommand operator=(const MoveActorCommand&) = delete;
	MoveActorCommand operator=(MoveActorCommand&&) = delete;

private:
	glm::vec2 m_MoveVec;
};

class ToggleMuteCommand final : public dae::Command
{
public:
	ToggleMuteCommand() = default;
	void Execute();

	~ToggleMuteCommand() = default;

	ToggleMuteCommand(const ToggleMuteCommand&) = delete;
	ToggleMuteCommand(ToggleMuteCommand&&) = delete;
	ToggleMuteCommand operator=(const ToggleMuteCommand&) = delete;
	ToggleMuteCommand operator=(ToggleMuteCommand&&) = delete;

private:
	uint8_t m_PrevEffectVol{ 128 };
	uint8_t m_PrevMusicVol{ 128 };
};

class MoveQBertCommand final : public dae::Command
{
public:
	MoveQBertCommand(QBertComponent* qbertComp, glm::ivec2 moveVec);
	void Execute();

	~MoveQBertCommand() = default;

	MoveQBertCommand(const MoveQBertCommand&) = delete;
	MoveQBertCommand(MoveQBertCommand&&) = delete;
	MoveQBertCommand operator=(const MoveQBertCommand&) = delete;
	MoveQBertCommand operator=(MoveQBertCommand&&) = delete;

private:
	QBertComponent* m_QBertComp{ nullptr };
	glm::ivec2 m_MoveVec{};
};