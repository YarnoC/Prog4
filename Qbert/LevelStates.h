#pragma once
#include <memory>
#include <vector>

class LevelComponent;
class CubeComponent;

class LevelState
{
public:
	virtual std::unique_ptr<LevelState> Update() { return nullptr; };
	virtual std::unique_ptr<LevelState> CheckTiles(std::vector<std::vector<CubeComponent*>>) { return nullptr; };
	virtual void OnEnter() {};
	virtual void OnExit() {};

	~LevelState() = default;

	LevelState(const LevelState&) = delete;
	LevelState(LevelState&&) = delete;
	LevelState& operator=(const LevelState&) = delete;
	LevelState& operator=(LevelState&&) = delete;

protected:
	LevelState(LevelComponent* levelComp);

	LevelComponent* m_LevelComp;

private:
};

class LevelPlayingState final : public LevelState
{
public:
	std::unique_ptr<LevelState> CheckTiles(std::vector<std::vector<CubeComponent*>> levelVec) override;

	void OnEnter() override;

	LevelPlayingState(LevelComponent* levelComp);

	~LevelPlayingState() = default;

	LevelPlayingState(const LevelPlayingState&) = delete;
	LevelPlayingState(LevelPlayingState&&) = delete;
	LevelPlayingState& operator=(const LevelPlayingState&) = delete;
	LevelPlayingState& operator=(LevelPlayingState&&) = delete;

private:

};

class LevelFinishedState final : public LevelState
{
public:
	std::unique_ptr<LevelState> Update() override;
	void OnEnter() override;

	LevelFinishedState(LevelComponent* levelComp);

	~LevelFinishedState() = default;

	LevelFinishedState(const LevelFinishedState&) = delete;
	LevelFinishedState(LevelFinishedState&&) = delete;
	LevelFinishedState& operator=(const LevelFinishedState&) = delete;
	LevelFinishedState& operator=(LevelFinishedState&&) = delete;

private:
	double m_TransitionTimeLeft{ 3.0 };
	float m_BlinkTimer{};
};