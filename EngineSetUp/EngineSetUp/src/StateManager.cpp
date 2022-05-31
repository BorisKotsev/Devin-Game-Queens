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

void StateManager::update()
{
	m_currState->run();
}

void StateManager::destroyLastState()
{
	m_currState->destroy();

	delete m_currState;
	m_currState = nullptr;
}
