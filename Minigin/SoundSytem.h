#pragma once
namespace dae
{

class SoundSytem
{
public:
	virtual void Play(const unsigned short soundId, const float volume) = 0;
	virtual ~SoundSytem() = default;

	SoundSytem(const SoundSytem&) = delete;
	SoundSytem(SoundSytem&&) = delete;
	SoundSytem& operator=(const SoundSytem&) = delete;
	SoundSytem& operator(SoundSytem&&) = delete;
};

class NullSoundSystem final : public SoundSytem
{
public:
	void Play(const unsigned short soundId, const float volume) {};

	~NullSoundSystem() = default;

	NullSoundSystem(const NullSoundSystem&) = delete;
	NullSoundSystem(NullSoundSystem&&) = delete;
	NullSoundSystem& operator=(const NullSoundSystem&) = delete;
	NullSoundSystem& operator=(NullSoundSystem&&) = delete;
};

}
