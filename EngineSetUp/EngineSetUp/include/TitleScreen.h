#pragma once

#include "defines.h"
#include "State.h"

class TitleScreen : public State
{
public :
	TitleScreen();
	~TitleScreen();

private:
	Drawable m_titleScreen;
};