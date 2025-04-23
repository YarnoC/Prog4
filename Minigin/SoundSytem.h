#pragma once
#include <string>

namespace dae
{

class SoundSytem
{
public:
	virtual void Play(unsigned short soundId, uint8_t volume, bool looping) = 0;
	[[nodiscard]] virtual unsigned short LoadWav(const std::string& filePath) = 0;

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
	void Play(unsigned short soundId, uint8_t volume) {};
	[[nodiscard]] unsigned short LoadWav(const std::string& filepath) {};

	//add default ctor
	NullSoundSystem() = default;
	~NullSoundSystem() = default;

	NullSoundSystem(const NullSoundSystem&) = delete;
	NullSoundSystem(NullSoundSystem&&) = delete;
	NullSoundSystem& operator=(const NullSoundSystem&) = delete;
	NullSoundSystem& operator=(NullSoundSystem&&) = delete;
};

}
