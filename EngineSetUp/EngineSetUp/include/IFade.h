#pragma once 

#include <fstream>

#include "Engine.h"

class IFade
{
public:
	IFade();
	~IFade();

	void initTextures(string backgroundAdr, string foregroundAdr, SDL_Renderer* renderer);

	void increaseOpacity();
	void decreaseOpacity();

	void setOpacityPerFrame(int opacityPerFrame);
protected:
	int m_opacity;
	int m_opacityPerFrame;

	Drawable m_background;
	Drawable m_foreground;
};