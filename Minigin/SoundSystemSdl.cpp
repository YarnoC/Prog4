#include "SoundSystemSdl.h"
#include <algorithm>
#include <thread>
#include <mutex>
#include <map>

void dae::SoundSystemSdl::Play(unsigned short soundId, uint8_t volume, bool looping)
{
	//sdl mixer uses volume 0 - 128 so gotta remap 0 - 100 to 0 - 128
	//any value below 0 does not change the volume, and any value above 128 (here userinput 100) gets set to 128
	auto newVol = static_cast<uint8_t>(1.28f * volume);

	std::lock_guard<std::mutex> lg(m_QMutex);
	m_AudioQueue->emplace(AudioRequest{ soundId, newVol, looping });
}

dae::SoundSystemSdl::SoundSystemSdl()
	: SoundSytem(),
	m_AudioThread{ [this](std::stop_token stopToken) {this->HandleAudio(std::move(stopToken)); }}
{

}

void dae::SoundSystemSdl::HandleAudio(std::stop_token&& stopToken)
{

}

struct dae::SoundSystemSdl::SdlImpl
{
	//use normal map
};
