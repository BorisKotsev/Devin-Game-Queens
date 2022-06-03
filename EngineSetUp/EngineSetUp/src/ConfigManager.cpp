#include "ConfigManager.h"
#include "World.h"

Entity* ConfigManager::m_enityModel = nullptr;

ConfigManager::ConfigManager()
{
}

ConfigManager::~ConfigManager()
{
}

void ConfigManager::load()
{
	loadEntity();
}

void ConfigManager::loadEntity()
{
	m_enityModel = new Entity();
	m_enityModel->load("entity");
}
