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
}

void Game::destroy()
{
}

void Game::run()
{
	m_grid.update();
	m_grid.draw();
}

int Game::winCondition(bool winner)
{
	if (winner)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
	return -1;
}
