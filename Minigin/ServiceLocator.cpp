#include "ServiceLocator.h"

std::unique_ptr<dae::SoundSytem>dae::ServiceLocator::m_SoundInstance = std::make_unique<dae::NullSoundSystem>();