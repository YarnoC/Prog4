#pragma once
#include "SoundSytem.h"
#include <memory>
#include <thread>
#include <queue>
#include <mutex>
#include <unordered_map>

namespace dae
{

class SoundSystemSdl final : public SoundSytem
{
public:
	void Play(short soundId, uint8_t volume, bool looping) override;
	//the return value should be stored and used as the soundId value in the play value
	[[nodiscard]] short LoadEffect(const std::string& filepath) override;
	[[nodiscard]] short LoadMusic(const std::string& filepath) override;
	void SetMasterVolume(uint8_t volume) override;
	void SetEffectsVolume(uint8_t volume) override;
	void SetMusicVolume(uint8_t volume) override;
	void PauseMusic() override;
	void ResumeMusic() override;
	void StopAllEffects() override;
	void StopMusic() override;

	SoundSystemSdl();

	~SoundSystemSdl();

	SoundSystemSdl(const SoundSystemSdl&) = delete;
	SoundSystemSdl(SoundSystemSdl&&) = delete;
	SoundSystemSdl& operator=(const SoundSystemSdl&) = delete;
	SoundSystemSdl& operator=(SoundSystemSdl&&) = delete;

private:
	struct SdlImpl;
	std::unique_ptr<SdlImpl> m_pImpl;

	//positive for effects, negative for music
	short m_CurrentEffectIndex{ 0 };
	short m_CurrentMusicIndex{ -1 };

	std::jthread m_AudioThread;
	void HandleAudio(std::stop_token&& stopToken);

	struct AudioRequest
	{
		const short soundId{};
		const bool looping{};
	};

	std::unique_ptr<std::queue<AudioRequest>> m_AudioQueue;
	std::mutex m_QMutex;
	std::condition_variable m_PlayCv{};
	std::mutex m_WaitPlayMutex;
	std::unordered_map<std::string, short> m_LoadedSounds{};
};

}
