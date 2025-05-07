#pragma once
#include <string>

namespace dae
{

class SoundSytem
{
public:
	virtual void Play(short soundId, uint8_t volume, bool looping) = 0;
	[[nodiscard]] virtual short LoadEffect(const std::string& filePath) = 0;
	[[nodiscard]] virtual short LoadMusic(const std::string& filepath) = 0;
	virtual void SetMasterVolume(uint8_t volume) = 0;
	virtual void SetEffectsVolume(uint8_t volume) = 0;
	virtual void SetMusicVolume(uint8_t volume) = 0;
	virtual void PauseMusic() = 0;
	virtual void ResumeMusic() = 0;
	virtual void StopAllEffects() = 0;
	virtual void StopMusic() = 0;

	SoundSytem() = default;
	virtual ~SoundSytem() = default;

	SoundSytem(const SoundSytem&) = delete;
	SoundSytem(SoundSytem&&) = delete;
	SoundSytem& operator=(const SoundSytem&) = delete;
	SoundSytem& operator=(SoundSytem&&) = delete;
};

class NullSoundSystem final : public SoundSytem
{
public:
	void Play(short, uint8_t, bool) override {};
	[[nodiscard]] short LoadEffect(const std::string&) override { return 0; };
	[[nodiscard]] short LoadMusic(const std::string&) override { return 0; };
	void SetMasterVolume(uint8_t) override {};
	void SetEffectsVolume(uint8_t) override {};
	void SetMusicVolume(uint8_t) override {};
	void PauseMusic() override {};
	void ResumeMusic() override {};
	void StopAllEffects() override {};
	void StopMusic() override {};

	NullSoundSystem() = default;
	~NullSoundSystem() = default;

	NullSoundSystem(const NullSoundSystem&) = delete;
	NullSoundSystem(NullSoundSystem&&) = delete;
	NullSoundSystem& operator=(const NullSoundSystem&) = delete;
	NullSoundSystem& operator=(NullSoundSystem&&) = delete;
};

}
