#pragma once

#include <fstream>

#include "defines.h"
#include "State.h"
#include "Button.h"
#include "InputField.h"

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

	Drawable m_rows;
	Drawable m_cols;
	Drawable m_boardSize;

	Button* m_onePlayerBtn;
	Button* m_twoPlayersBtn;
	Button* m_exitBtn;
	
	InputField m_rowsField;
	InputField m_colsField;
};