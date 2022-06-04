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

	string tmp, menuImg, onePlayerBtn, twoPlayersBtn, exitPath, rowsImg, colsImg;

	stream.open(CONFIG_FOLDER + MENU_FOLDER + "menu.txt");
	
	stream >> tmp >> m_menu.rect.x >> m_menu.rect.y >> m_menu.rect.w >> m_menu.rect.h;
	stream >> tmp >> menuImg;
	stream >> tmp >> onePlayerBtn;
	stream >> tmp >> twoPlayersBtn;
	stream >> tmp >> exitPath;
	stream >> tmp >> m_rows.rect.x >> m_rows.rect.y >> m_rows.rect.w >> m_rows.rect.h;
	stream >> tmp >> rowsImg;
	stream >> tmp >> m_cols.rect.x >> m_cols.rect.y >> m_cols.rect.w >> m_cols.rect.h;
	stream >> tmp >> colsImg;

	stream.close();

	m_menu.texture = loadTexture(MENU_FOLDER + menuImg);

	m_rows.texture = loadTexture(MENU_FOLDER + rowsImg);
	m_cols.texture = loadTexture(MENU_FOLDER + colsImg);

	m_onePlayerBtn->init(onePlayerBtn, MENU_FOLDER);
	m_twoPlayersBtn->init(twoPlayersBtn, MENU_FOLDER);
	m_exitBtn->init(exitPath, MENU_FOLDER);
}

void Menu::run()
{
	drawObject(m_menu);
	
	drawObject(m_rows);
	drawObject(m_cols);
	
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