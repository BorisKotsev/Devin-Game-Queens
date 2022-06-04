#include "ConfigManager.h"
#include "World.h"

Entity* ConfigManager::m_enityModel = nullptr;
Drawable* ConfigManager::m_invalidInputMsg = nullptr;

ConfigManager::ConfigManager()
{
}

ConfigManager::~ConfigManager()
{
}

void ConfigManager::load()
{
	loadEntity();
	loadInvalidInputMsg();
}

void ConfigManager::loadEntity()
{
	m_enityModel = new Entity();
	m_enityModel->load("entity");
}

void ConfigManager::loadInvalidInputMsg()
{
	m_invalidInputMsg = new Drawable();
	
	fstream stream;

	string tmp, invalidInputMsg;

	stream.open(CONFIG_FOLDER + MENU_FOLDER + "invalidMsg.txt");

	stream >> tmp >> m_invalidInputMsg->rect.x >> m_invalidInputMsg->rect.y >> m_invalidInputMsg->rect.w >> m_invalidInputMsg->rect.h;
	stream >> tmp >> invalidInputMsg;

	stream.close();

	m_invalidInputMsg->texture = loadTexture(MENU_FOLDER + invalidInputMsg);
}
