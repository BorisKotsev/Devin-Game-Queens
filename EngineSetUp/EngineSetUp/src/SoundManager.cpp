#include "SoundManager.h"

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{
	
}

void SoundManager::init()
{
	fstream stream;

	string tmp;

	stream.open(SOUND_FOLDER + "music.txt");

	stream >> tmp >> _backgroundStr;
	
	stream.close();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		printf("%s", Mix_GetError());
	}

	m_backgroundMusic = Mix_LoadWAV((SOUND_FOLDER + _backgroundStr).c_str());
}

void SoundManager::playSound(string sound)
{
	Mix_AllocateChannels(3);

	if (sound == _backgroundStr)
	{
		Mix_PlayChannel(1, m_backgroundMusic, -1);
		Mix_Volume(1, 5);
	}
}

void SoundManager::destroy()
{
	Mix_FreeChunk(m_backgroundMusic);
	m_backgroundMusic = NULL;
}
