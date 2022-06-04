#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init()
{
	m_grid.load(-1);
	Entity::m_grid = &m_grid;

	m_inputField.init("enterName.txt", "");

	fstream stream;

	string tmp, player1OnTurn, player2OnTurn;

	stream.open(CONFIG_FOLDER + GAME_FOLDER + "game.txt");

	stream >> tmp >> m_player1OnTurn.rect.x >> m_player1OnTurn.rect.y >> m_player1OnTurn.rect.w >> m_player1OnTurn.rect.h;
	stream >> tmp >> player1OnTurn >> player2OnTurn;
	
	stream.close();

	m_player2OnTurn.rect = m_player1OnTurn.rect;
	
	m_player1OnTurn.texture = loadTexture(GAME_FOLDER + player1OnTurn);
	m_player2OnTurn.texture = loadTexture(GAME_FOLDER + player2OnTurn);
}

void Game::destroy()
{
	
}

void Game::run()
{
	//m_inputField.update();
	m_grid.update();
	m_grid.draw();
	//m_inputField.draw();

	if (true) // player on turn
	{
		//drawObject(m_player1OnTurn);
	}
	else
	{
		//drawObject(m_player2OnTurn);
	}
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
