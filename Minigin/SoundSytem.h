#pragma once
namespace dae
{

class SoundSytem
{
public:
	virtual ~SoundSystem() = default;
	virtual void Play(const unsigned short soundId, const float volume) = 0;

	SoundSystem(const SoundSytem&) = delete;
	SoundSystem(SoundSystem&&) = delete;
	SoundSystem& operator=(const SoundSystem&) = delete;
	SoundSystem& operator(SoundSystem&&) = delete;
};

}
