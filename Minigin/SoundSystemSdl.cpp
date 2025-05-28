#include "SoundSystemSdl.h"
#include "SDL_mixer.h"
#include <algorithm>
#include <thread>
#include <mutex>
#include <map>
#include <cassert>
#include <variant>
#include <iostream>

#include <filesystem>

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
	m_PlayCv.notify_all();
}

short dae::SoundSystemSdl::LoadEffect(const std::string& filepath)
{
	auto fullPath = m_SoundsDir +  "/" + filepath;

	auto [valPair, emplaceSuccess] = m_LoadedSounds.try_emplace(fullPath, m_CurrentEffectIndex);

	if (emplaceSuccess)
	{
		std::unique_ptr<Mix_Chunk, ChunkDtor> uptr(Mix_LoadWAV(fullPath.c_str()));
		if (uptr == nullptr)
		{
			std::cout << "at index " << m_CurrentEffectIndex << " " << Mix_GetError() << std::endl;
		}
		m_pImpl->m_AudioEffectCache.emplace(m_CurrentEffectIndex, std::move(uptr));
		return m_CurrentEffectIndex++; //post increment so old value gets returned and then updated
	}
	else
	{
		//if emplace fails (sound already exists), the value of the existing entry is returned in valPair, ->second here is used to retrieve the soundId
		return valPair->second;
	}
}

short dae::SoundSystemSdl::LoadMusic(const std::string& filepath)
{
	auto fullPath = m_SoundsDir + "/" + filepath;

	auto [valPair, emplaceSuccess] = m_LoadedSounds.try_emplace(fullPath, m_CurrentEffectIndex);

	if (emplaceSuccess)
	{
		std::unique_ptr<Mix_Music, MusicDtor> uptr(Mix_LoadMUS(fullPath.c_str()));
		m_pImpl->m_MusicCache.emplace(m_CurrentMusicIndex, std::move(uptr));
		return m_CurrentMusicIndex--;
	}
	else
	{
		return valPair->second;
	}

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

//void dae::SoundSystemSdl::SetDataPath(const std::string& dataPath)
//{
//	m_SoundsDir = dataPath;
//}

dae::SoundSystemSdl::SoundSystemSdl()
	: SoundSytem(),
	m_pImpl{ std::make_unique<dae::SoundSystemSdl::SdlImpl>() },
	m_AudioThread{ [this](std::stop_token stopToken) { this->HandleAudio(std::move(stopToken)); }},
	m_AudioQueue{ std::make_unique<std::queue<AudioRequest>>() }
{
	//sdl mixer init
	int flags = MIX_INIT_MP3 || MIX_INIT_OGG;
	auto result = Mix_Init(flags); //returns 0 if fails
	assert(result == flags); //check if all flags were succesfully set //assert fails
	result = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096); //returns 0 for succes, -1 for failure
	assert(result == 0);
}

dae::SoundSystemSdl::~SoundSystemSdl()
{
	m_AudioThread.request_stop();
	m_PlayCv.notify_all();
	m_AudioThread.join();
}

void dae::SoundSystemSdl::HandleAudio(std::stop_token&& stopToken)
{
	//m_pImpl = std::make_unique<dae::SoundSystemSdl::SdlImpl>();

	//sdl mixer init
	//auto flags = MIX_INIT_MP3;
	//auto result = Mix_Init(flags); //returns 0 if fails
	//assert(result == flags); //check if all flags were succesfully set //assert fails
	//result = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096); //returns 0 for succes, -1 for failure
	//assert(result == 0);

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

		//sdl mixer allows for a certain amount of loops or a (not really) infinite loop by inputting -1, here we're only exposing infinite loop or no loop to the users
		//so true (1) * -1 = -1 and false (0) * -1 = 0
		//constexpr int loopLogic{ -1 };
		int loops{ request.looping * -1 };

		if (request.soundId >= 0)
		{
			Mix_PlayChannel(-1, m_pImpl->m_AudioEffectCache[request.soundId].get(), loops);
		}
		else
		{
			Mix_PlayMusic(m_pImpl->m_MusicCache[request.soundId].get(), loops);
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


