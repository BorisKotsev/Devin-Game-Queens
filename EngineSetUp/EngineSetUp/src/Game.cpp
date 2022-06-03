#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init()
{
	m_config.load();
	m_grid.load();
	Entity::m_grid = &m_grid;

	m_grid.addEntity(int2{ 0,0 });
	m_inputField.init("enterName.txt", "");
}

void Game::destroy()
{
}

void Game::run()
{
	m_inputField.update();
	m_grid.update();
	m_grid.draw();
	m_inputField.draw();
}
