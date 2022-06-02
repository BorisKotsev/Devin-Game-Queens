#include "WinScreen.h"
#include "World.h"

extern World world;

WinScreen::WinScreen()
{
	m_playBtn = new Button();
	m_exitBtn = new Button();
}

WinScreen::~WinScreen()
{
	
}

void WinScreen::init()
{
	fstream stream;

	string tmp, background, pl1, pl2, playBtnPath, exitBtnPath;

	stream.open(CONFIG_FOLDER + WIN_SCREEN_FOLDER + "winScreen.txt");

	stream >> tmp >> background;
	stream >> tmp >> m_winScreenPl1.rect.x >> m_winScreenPl1.rect.y >> m_winScreenPl1.rect.w >> m_winScreenPl1.rect.h;
	stream >> tmp >> pl1 >> pl2;
	stream >> tmp >> playBtnPath;
	stream >> tmp >> exitBtnPath;
	
	stream.close();
	
	m_background = loadTexture(WIN_SCREEN_FOLDER + background);
	
	m_winScreenPl2.rect = m_winScreenPl1.rect;

	m_winScreenPl1.texture = loadTexture(WIN_SCREEN_FOLDER + pl1);
	m_winScreenPl2.texture = loadTexture(WIN_SCREEN_FOLDER + pl2);

	m_playBtn->init(playBtnPath, MENU_FOLDER);
	m_exitBtn->init(exitBtnPath, MENU_FOLDER);
}

void WinScreen::run()
{
	if (MouseIsInRect(world.m_inputManager.m_mouseCoor, m_playBtn->getRect())
		&& world.m_inputManager.m_mouseIsPressed)
	{
		world.m_stateManager.changeGameState(GAME_STATE::GAME);
	}

	if (MouseIsInRect(world.m_inputManager.m_mouseCoor, m_exitBtn->getRect())
		&& world.m_inputManager.m_mouseIsPressed)
	{
		world.m_stateManager.changeGameState(GAME_STATE::NONE);
	}
	
	drawObject(m_background);
	
	if (true)
	{
		drawObject(m_winScreenPl1);
	}
	else
	{
		drawObject(m_winScreenPl2);
	}

	m_playBtn->update();
	m_playBtn->draw();

	m_exitBtn->update();
	m_exitBtn->draw();
}

void WinScreen::destroy()
{
	SDL_DestroyTexture(m_background);
	SDL_DestroyTexture(m_winScreenPl1.texture);
	SDL_DestroyTexture(m_winScreenPl2.texture);

	m_playBtn->destroy();
	m_exitBtn->destroy();
}