#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class GameObject;
	class Scene;
}

class GameStateComponent final : public dae::Component, public dae::Observer
{
public:

	void OnNotify(const dae::Event& e, dae::Component* callerComp) override;

	enum class GameMode
	{
		Solo,
		Coop,
		Versus,
	};

	static const GameMode& GetGameMode();

	void NextMenuOption(bool reverse = false);
	void UpdateCursorPos(dae::GameObject* obj);

	GameStateComponent(dae::GameObject* owner);

	~GameStateComponent() = default;

	GameStateComponent(const GameStateComponent&) = delete;
	GameStateComponent(GameStateComponent&&) = delete;
	GameStateComponent& operator=(const GameStateComponent&) = delete;
	GameStateComponent& operator=(GameStateComponent&&) = delete;

private:
	static GameMode m_GameMode;
	dae::Scene* m_WorkingScene{ nullptr };
	int m_Score{};
	int m_MenuChoice{};
	
	void LoadLevel();
	void LoadGameOverScreen();
	void LoadMainMenu();
	void LoadSinglePlayer();
};