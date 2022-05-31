#pragma once

#include "Game.h"
#include "TitleScreen.h"

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
class StateManager
{
public:
	StateManager();
	~StateManager();

	GAME_STATE m_gameState;

	Game* m_game;
	TitleScreen* m_titleScreen;
	
	State* m_currState;
	
	void init(GAME_STATE _state);
	void update();

	void changeGameState(GAME_STATE _state);

private:
	void initNewState();
	void destroyLastState();
};