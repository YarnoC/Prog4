#include "SoundSystemSdl.h"
#include "SDL_mixer.h"
#include <algorithm>
#include <thread>
#include <mutex>
#include <map>
#include <cassert>
#include <variant>

struct ChunkDtor
{
	void operator() (Mix_Chunk* chunkPtr) const
	{
		Mix_FreeChunk(chunkPtr);
	}
};

struct MusicDtor
{
	void operator() (Mix_Music* musicPtr) const
	{
		Mix_FreeMusic(musicPtr);
	}
};

struct dae::SoundSystemSdl::SdlImpl
{
	//std::map<short, std::variant<std::unique_ptr<Mix_Chunk>, std::unique_ptr<Mix_Music>>> m_AudioCache;
	std::map<short, std::unique_ptr<Mix_Chunk, ChunkDtor>> m_AudioEffectCache;
	std::map<short, std::unique_ptr<Mix_Music, MusicDtor>> m_MusicCache;
	std::mutex m_CacheMutex;
};

void dae::SoundSystemSdl::Play(short soundId, uint8_t volume, bool looping)
{
	//sdl mixer uses volume 0 - 128 so gotta remap 0 - 100 to 0 - 128
	//any value below 0 does not change the volume, and any value above 128 (here userinput 100) gets set to 128
	auto newVol = static_cast<uint8_t>(1.28f * volume);
	if (soundId >= 0)
	{
		Mix_VolumeChunk(m_pImpl->m_AudioEffectCache[soundId].get(), newVol);
	}
	else
	{
		Mix_VolumeMusic(newVol);
	}

	std::lock_guard<std::mutex> lg(m_QMutex);
	m_AudioQueue->emplace(AudioRequest{ soundId, looping });
}

short dae::SoundSystemSdl::LoadEffect(const std::string& filepath)
{
	std::unique_ptr<Mix_Chunk, ChunkDtor> uptr(Mix_LoadWAV(filepath.c_str()));
	m_pImpl->m_AudioEffectCache.emplace(m_CurrentEffectIndex, std::move(uptr));
	return m_CurrentEffectIndex++; //post increment so old value gets returned and then updated
}

short dae::SoundSystemSdl::LoadMusic(const std::string& filepath)
{
	std::unique_ptr<Mix_Music, ChunkDtor> uptr(Mix_LoadMUS(filepath.c_str()));
	m_pImpl->m_MusicCache.emplace(m_CurrentMusicIndex, std::move(uptr));
	return m_CurrentMusicIndex--;
}

void dae::SoundSystemSdl::SetMasterVolume(uint8_t volume)
{
	SetEffectsVolume(volume);
	SetMusicVolume(volume);
}

void dae::SoundSystemSdl::SetEffectsVolume(uint8_t volume)
{
	auto newVol = static_cast<uint8_t>(1.28f * volume);
	//set vol for all channels
	Mix_Volume(-1, newVol);
}

void dae::SoundSystemSdl::SetMusicVolume(uint8_t volume)
{
	auto newVol = static_cast<uint8_t>(1.28f * volume);
	Mix_VolumeMusic(newVol);
}

void dae::SoundSystemSdl::PauseMusic()
{
	Mix_PauseMusic();
}

void dae::SoundSystemSdl::ResumeMusic()
{
	Mix_ResumeMusic();
}

void dae::SoundSystemSdl::StopAllEffects()
{
	Mix_HaltChannel(-1);
}

void dae::SoundSystemSdl::StopMusic()
{
	Mix_HaltMusic();
}

dae::SoundSystemSdl::SoundSystemSdl()
	: SoundSytem(),
	m_AudioThread{ [this](std::stop_token stopToken) {this->HandleAudio(std::move(stopToken)); }}
{

}

dae::SoundSystemSdl::~SoundSystemSdl()
{
	//maybe not needed
}

void dae::SoundSystemSdl::HandleAudio(std::stop_token&& stopToken)
{
	m_pImpl = std::make_unique<dae::SoundSystemSdl::SdlImpl>();

	//sdl mixer init
	auto flags = MIX_INIT_WAVPACK | MIX_INIT_MP3;
	auto result = Mix_Init(flags); //returns 0 if fails
	assert(result == flags); //check if all flags were succesfully set
	result = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096); //returns 0 for succes, -1 for failure
	assert(result == 0);

	while (!stopToken.stop_requested())
	{
		std::unique_lock<std::mutex> playLock{m_WaitPlayMutex};
		m_PlayCv.wait(playLock, [this, &stopToken]() -> bool
			{
				std::lock_guard qLock{ m_QMutex };
				return !m_AudioQueue->empty() || stopToken.stop_requested();
			});

		if (stopToken.stop_requested()) break;

		m_QMutex.lock();

		auto request = m_AudioQueue->front();
		m_AudioQueue->pop();

		m_QMutex.unlock();

		if (request.soundId >= 0)
		{
			Mix_PlayChannel(-1, m_pImpl->m_AudioEffectCache[request.soundId].get(), request.looping);
		}
		else
		{
			Mix_PlayMusic(m_pImpl->m_MusicCache[request.soundId].get(), request.looping);
		}

	}

	//stopping all channels because freeing chunks while they are being played is a bad idea
	StopAllEffects();
	StopMusic();

	//clear vectors to trigger dtors of all uptrs of chunks and music
	m_pImpl->m_AudioEffectCache.clear();
	m_pImpl->m_MusicCache.clear();

	//sdl mixer shutdown
	Mix_CloseAudio();
	Mix_Quit();
}


