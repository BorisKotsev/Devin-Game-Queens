#include "Menu.h"
#include "World.h"

extern World world;

Menu::Menu()
{
	m_onePlayerBtn = new Button();
	m_twoPlayersBtn = new Button();
	m_exitBtn = new Button();
}

Menu::~Menu()
{
	
}

void Menu::init()
{
	fstream stream;

	string tmp, img, onePlayerBtn, twoPlayersBtn, exitPath;

	stream.open(CONFIG_FOLDER + MENU_FOLDER + "menu.txt");
	
	stream >> tmp >> m_menu.rect.x >> m_menu.rect.y >> m_menu.rect.w >> m_menu.rect.h;
	stream >> tmp >> img;
	stream >> tmp >> onePlayerBtn;
	stream >> tmp >> twoPlayersBtn;
	stream >> tmp >> exitPath;

	stream.close();

	m_menu.texture = loadTexture(MENU_FOLDER + img);

	m_onePlayerBtn->init(onePlayerBtn, MENU_FOLDER);
	m_twoPlayersBtn->init(twoPlayersBtn, MENU_FOLDER);
	m_exitBtn->init(exitPath, MENU_FOLDER);
}

void Menu::run()
{
	drawObject(m_menu);
	
	m_onePlayerBtn->update();
	m_onePlayerBtn->draw();

	m_twoPlayersBtn->update();
	m_twoPlayersBtn->draw();
	
	m_exitBtn->update();
	m_exitBtn->draw();
	
	if (MouseIsInRect(world.m_inputManager.m_mouseCoor, m_onePlayerBtn->getRect()) && world.m_inputManager.m_mouseIsPressed)
	{
		world.m_stateManager.changeGameState(GAME_STATE::GAME);
		return;
	}

	if (MouseIsInRect(world.m_inputManager.m_mouseCoor, m_twoPlayersBtn->getRect()) && world.m_inputManager.m_mouseIsPressed)
	{
		world.m_stateManager.changeGameState(GAME_STATE::GAME);
		return;
	}

	if (MouseIsInRect(world.m_inputManager.m_mouseCoor, m_exitBtn->getRect()) && world.m_inputManager.m_mouseIsPressed)
	{
		world.m_stateManager.changeGameState(GAME_STATE::NONE);
		return;
	}
}

void Menu::destroy()
{
	m_onePlayerBtn->destroy();
	m_twoPlayersBtn->destroy();
	m_exitBtn->destroy();
	
	SDL_DestroyTexture(m_menu.texture);
}