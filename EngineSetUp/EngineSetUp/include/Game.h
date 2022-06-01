#pragma once

#include "State.h"

class Game : public State
{
public:
	Game();
	~Game();
	void init();
	void destroy();
	void run();


private:

};