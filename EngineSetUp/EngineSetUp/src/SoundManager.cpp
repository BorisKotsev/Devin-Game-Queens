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

	string tmp, background, btnClick, queenPlaced;

	stream.open(SOUND_FOLDER + "music.txt");

	stream >> tmp >> background;
	stream >> tmp >> btnClick;
	stream >> tmp >> queenPlaced;
	
	stream.close();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		printf("%s", Mix_GetError());
	}

	m_backgroundMusic = Mix_LoadWAV((SOUND_FOLDER + background).c_str());
	m_buttonClick = Mix_LoadWAV((SOUND_FOLDER + btnClick).c_str());
	m_placeQueen = Mix_LoadWAV((SOUND_FOLDER + queenPlaced).c_str());

	playSound(SOUND::BACKGROUND);
}

void SoundManager::playSound(SOUND sound)
{
	Mix_AllocateChannels(4);

	switch (sound)
	{
	case SOUND::BACKGROUND:
		Mix_PlayChannel(1, m_backgroundMusic, -1);
		Mix_Volume(1, 10);
		break;
	case SOUND::BUTTON_CLICK:
		Mix_PlayChannel(2, m_buttonClick, 0);
		Mix_Volume(2, 10);
		break;
	case SOUND::PLACE_QUEEN:
		Mix_PlayChannel(3, m_placeQueen, 0);
		Mix_Volume(3, 10);
		break;
	default:
		break;
	}
}

void SoundManager::destroy()
{
	Mix_FreeChunk(m_backgroundMusic);
	m_backgroundMusic = NULL;

	Mix_FreeChunk(m_buttonClick);
	m_buttonClick = NULL;
	
	Mix_FreeChunk(m_placeQueen);
	m_placeQueen = NULL;
}
