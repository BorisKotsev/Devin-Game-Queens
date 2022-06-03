#include "IFade.h"

IFade::IFade()
{
	m_opacity = 255;
	m_opacityPerFrame = 1;
}

IFade::~IFade()
{
}

void IFade::initTextures(string backgroundAdr, string foregroundAdr, SDL_Renderer* renderer)
{
	m_background.texture = LoadTexture(backgroundAdr, renderer);
	m_foreground.texture = LoadTexture(foregroundAdr, renderer);
}

void IFade::increaseOpacity()
{
	m_opacity += m_opacityPerFrame;

	if (m_opacity > 255)
	{
		m_opacity = 255;
	}

	SDL_SetTextureAlphaMod(m_foreground.texture, m_opacity);
}

void IFade::decreaseOpacity()
{
	m_opacity -= m_opacityPerFrame;

	if (m_opacity < 0)
	{
		m_opacity = 0;
	}
	
	SDL_SetTextureAlphaMod(m_foreground.texture, m_opacity);
}

void IFade::setOpacityPerFrame(int opacityPerFrame)
{
	m_opacityPerFrame = opacityPerFrame;
}