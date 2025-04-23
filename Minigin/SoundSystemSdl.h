#pragma once
#include "SoundSytem.h"
#include <memory>
#include <thread>
#include <queue>
#include <mutex>

namespace dae
{

class SoundSystemSdl final : public SoundSytem
{
public:
	void Play(unsigned short soundId, uint8_t volume, bool looping) override;
	[[nodiscard]] unsigned short LoadWav(const std::string& filepath) override;

	SoundSystemSdl();

	~SoundSystemSdl() = default;

	SoundSystemSdl(const SoundSystemSdl&) = delete;
	SoundSystemSdl(SoundSystemSdl&&) = delete;
	SoundSystemSdl& operator=(const SoundSystemSdl&) = delete;
	SoundSystemSdl& operator=(SoundSystemSdl&&) = delete;

private:
	class SdlImpl;
	std::unique_ptr<SdlImpl> m_pImpl;

	std::jthread m_AudioThread;
	void HandleAudio(std::stop_token&& stopToken);

	struct AudioRequest
	{
		const unsigned short soundId{};
		const uint8_t volume{};
		const bool looping{};
	};

	std::unique_ptr<std::queue<AudioRequest>> m_AudioQueue;
	std::mutex m_QMutex;

};

}
