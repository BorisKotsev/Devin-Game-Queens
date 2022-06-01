#include "TitleScreen.h"
#include "World.h"

extern World world;

TitleScreen::TitleScreen()
{
	
}

TitleScreen::~TitleScreen()
{

}

void TitleScreen::init()
{
	fstream stream;
	
	string tmp, txt, logo;

	stream.open(CONFIG_FOLDER + TITLE_SCREEN_FOLDER + "titleScreen.txt");

	stream >> tmp >> m_titleScreenLogo.rect.x >> m_titleScreenLogo.rect.y >> m_titleScreenLogo.rect.w >> m_titleScreenLogo.rect.h;
	stream >> tmp >> logo;
	stream >> tmp >> m_titleScreenText.rect.x >> m_titleScreenText.rect.y >> m_titleScreenText.rect.w >> m_titleScreenText.rect.h;
	stream >> tmp >> txt;
	stream >> tmp >> m_titleScreenText.opacity;
	stream >> tmp >> m_titleScreenText.changePerFrame;
	
	stream.close();

	m_titleScreenLogo.texture = loadTexture(TITLE_SCREEN_FOLDER + logo);
	m_titleScreenText.texture = loadTexture(TITLE_SCREEN_FOLDER + txt);
}

void TitleScreen::run()
{
	drawObject(m_titleScreenLogo);

	changeOpacity(m_titleScreenText.changePerFrame);
	
	drawObject(m_titleScreenText);
}

void TitleScreen::destroy()
{
	SDL_DestroyTexture(m_titleScreenText.texture);
	SDL_DestroyTexture(m_titleScreenLogo.texture);
}

void TitleScreen::changeOpacity(int changePerFrame)
{
	if (m_titleScreenText.opacity < 255)
	{
		m_titleScreenText.opacity += changePerFrame;
	}
	else
	{
		m_titleScreenText.opacity = 0;
	}
}