#include "StateManager.h"

StateManager::StateManager()
{
	m_gameState = GAME_STATE::NONE;
	m_currState = nullptr;
}

StateManager::~StateManager()
{
	m_gameState = GAME_STATE::NONE;
	m_currState = nullptr;
}

void StateManager::changeGameState(GAME_STATE _state)
{
	destroyLastState();

	m_gameState = _state;

	initNewState();
}

void StateManager::initNewState()
{
	switch (m_gameState)
	{
	case GAME_STATE::GAME:
		m_game = new Game();
		m_currState = m_game;
		break;
	case GAME_STATE::TITLE_SCREEN:
		m_titleScreen = new TitleScreen();
		m_currState = m_titleScreen;
		break;
	case GAME_STATE::MENU:
		m_menu = new Menu();
		m_currState = m_menu;
		break;
	default:
		break;
	}

	m_currState->init();
}

void StateManager::init(GAME_STATE _state)
{
	m_gameState = _state;

	initNewState();
}

void StateManager::run()
{
	m_currState->run();
}

void StateManager::destroyLastState()
{
	m_currState->destroy();

	delete m_currState;
	m_currState = nullptr;
}
