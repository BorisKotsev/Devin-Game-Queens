#include "ConfigManager.h"
#include "World.h"

Entity* ConfigManager::m_enityModelPlayer1 = nullptr;
Entity* ConfigManager::m_enityModelPlayer2 = nullptr;
Entity* ConfigManager::m_enityModelEnemy = nullptr;

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
	m_enityModelPlayer1 = new Entity();
	m_enityModelPlayer1->load("player1");
	m_enityModelPlayer2 = new Entity();
	m_enityModelPlayer2->load("player2");
	m_enityModelEnemy = new Entity();
	m_enityModelEnemy->load("ai");
}
