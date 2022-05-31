#include "Menu.h"
#include "World.h"

extern World world;

Menu::Menu()
{
	m_playBtn = new Button();
	m_exitBtn = new Button();
}

Menu::~Menu()
{
	
}

void Menu::init()
{
	fstream stream;

	string tmp, img, playBtnPath, exitPath;

	stream.open(CONFIG_FOLDER + MENU_FOLDER + "menu.txt");
	
	stream >> tmp >> m_menu.rect.x >> m_menu.rect.y >> m_menu.rect.w >> m_menu.rect.h;
	stream >> tmp >> img;
	stream >> tmp >> playBtnPath;
	stream >> tmp >> exitPath;

	stream.close();

	m_menu.texture = loadTexture(MENU_FOLDER + img);

	m_playBtn->init(playBtnPath, MENU_FOLDER);
	m_exitBtn->init(exitPath, MENU_FOLDER);
}

void Menu::run()
{
	drawObject(m_menu);
	
	m_playBtn->update();
	m_playBtn->draw();

	m_exitBtn->update();
	m_exitBtn->draw();
}

void Menu::destroy()
{
	m_playBtn->destroy();
	m_exitBtn->destroy();
	
	SDL_DestroyTexture(m_menu.texture);
}