#pragma once
#include <memory>
#include "SoundSytem.h"

namespace dae
{

class ServiceLocator final
{
public:
	static SoundSytem& GetSoundSystem() { return *m_SoundInstance; }
	static void RegisterSoundSytem(std::unique_ptr<SoundSytem>&& soundSystem)
	{
		m_SoundInstance = soundSystem == nullptr ? std::make_unique<NullSoundSystem>() : std::move(soundSystem);
	}
private:
	static std::unique_ptr<SoundSytem> m_SoundInstance;
};

}
