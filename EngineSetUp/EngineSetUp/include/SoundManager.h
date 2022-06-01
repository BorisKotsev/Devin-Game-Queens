#pragma once

#include <SDL_mixer.h>
#include <fstream>

#include "defines.h"

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	
	void init();
	void playSound(string sound);
	void destroy();
	
private:
	string _backgroundStr;

	Mix_Chunk* m_backgroundMusic;
};