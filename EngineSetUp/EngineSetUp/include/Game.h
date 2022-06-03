#pragma once

#include "State.h"
#include "Grid.h"
#include "ConfigManager.h"

class Game : public State
{
public:

	Game();
	~Game();

	void init();
	void destroy();
	void run();

	int winCondition(bool winner);
private:

	ConfigManager m_config;
	Grid m_grid;
	
};