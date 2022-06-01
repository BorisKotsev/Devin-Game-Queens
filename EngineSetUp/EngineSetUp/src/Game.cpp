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
	m_grid.createByGridSquareSize(m_config.m_gridModel.coordinates, m_config.m_gridModel.dimensions, m_config.m_gridModel.borderThickness, m_config.m_gridModel.squareSize, m_config.m_gridModel.borderTexture, m_config.m_gridModel.squareTexture);

}

void Game::destroy()
{
}

void Game::run()
{
	m_grid.draw();
}
