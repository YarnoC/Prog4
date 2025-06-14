#pragma once
#include "Command.h"
#include "vec2.hpp"

class QBertComponent;
class LevelComponent;
class GameStateComponent;

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

class SkipLevelCommand final : public dae::Command
{
public:
	SkipLevelCommand(LevelComponent* levelComp, QBertComponent* qbertComp, QBertComponent* qbertCompP2 = nullptr);
	void Execute();

	~SkipLevelCommand() = default;

	SkipLevelCommand(const SkipLevelCommand&) = delete;
	SkipLevelCommand(SkipLevelCommand&&) = delete;
	SkipLevelCommand& operator=(const SkipLevelCommand&) = delete;
	SkipLevelCommand& operator=(SkipLevelCommand&&) = delete;

private:
	LevelComponent* m_LevelComp{ nullptr };
	QBertComponent* m_QBertComp{ nullptr };
	QBertComponent* m_QBertComp2{ nullptr };
};

class ReturnToMenuCmd final : public dae::Command
{
public:
	ReturnToMenuCmd(GameStateComponent* gameStateComp);
	void Execute();

	ReturnToMenuCmd(const ReturnToMenuCmd&) = delete;
	ReturnToMenuCmd(ReturnToMenuCmd&&) = delete;
	ReturnToMenuCmd& operator=(const ReturnToMenuCmd&) = delete;
	ReturnToMenuCmd& operator=(ReturnToMenuCmd&&) = delete;

private:
	GameStateComponent* m_GameStateComp{ nullptr };
};

class SelectMenuCmd final : public dae::Command
{
public:
	SelectMenuCmd(GameStateComponent* gameStateComp, dae::GameObject* obj, bool reverse = false);
	void Execute();

	~SelectMenuCmd() = default;

	SelectMenuCmd(const SelectMenuCmd&) = delete;
	SelectMenuCmd(SelectMenuCmd&&) = delete;
	SelectMenuCmd& operator=(const SelectMenuCmd&) = delete;
	SelectMenuCmd& operator=(SelectMenuCmd&&) = delete;

private:
	GameStateComponent* m_GameStateComp{ nullptr };
	dae::GameObject* m_Obj;
	bool m_Reverse{ false };
};

class ConfirmChoice final : public dae::Command
{
public:
	ConfirmChoice(GameStateComponent* gameStateComp);
	void Execute();

private:
	GameStateComponent* m_GameStateComp{ nullptr };
};