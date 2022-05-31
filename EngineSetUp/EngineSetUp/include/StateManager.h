#pragma once

#include "Game.h"

enum class GAME_STATE
{
	NONE = 0,
	REGISTER = 1,
	LOGIN = 2,
	LOBBY_AREA = 3,
	MATCHMAKING_CLIENT = 4,
	GAME = 5
};

/*
* \brief managing game states
* After switching to the next game state, delete the
* old one and all the create a new one. Loading screens
* must be playd between the creation and destruction of
* objects
*/
class GameManager
{
public:
	GameManager();
	~GameManager();

	GAME_STATE m_gameState;

	State* m_currState;

	void init(GAME_STATE _state);
	void update();

	void changeGameState(GAME_STATE _state);

private:
	void initNewState();
	void destroyLastState();
};