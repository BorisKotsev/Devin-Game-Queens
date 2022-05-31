#pragma once

#include "State.h"

class Game : public State
{
public:
	void init();
	void destroy();
	void run();
};