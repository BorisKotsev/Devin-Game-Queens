#pragma once

#include <fstream>

#include "defines.h"
#include "State.h"
#include "Button.h"

class Menu : public State
{
public:
	Menu();
	~Menu();

	void init();
	void run();
	void destroy();
	
private: 
	Drawable m_menu;

	Button* m_playBtn;
	Button* m_exitBtn;
};