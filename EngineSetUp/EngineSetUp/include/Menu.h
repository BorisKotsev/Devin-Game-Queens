#pragma once

#include <fstream>

#include "defines.h"
#include "State.h"
#include "Button.h"
#include "InputField.h"
#include "PopUp.h"

class Menu : public State
{
public:
	Menu();
	~Menu();

	void init();
	void run();
	void destroy();
	
private: 

	bool m_isValid;
	
	Drawable m_menu;
	Drawable m_rows;
	Drawable m_cols;
	Drawable m_boardSize;
	
	Drawable* m_invalidMsg;

	Button* m_onePlayerBtn;
	Button* m_twoPlayersBtn;
	Button* m_exitBtn;
	
	InputField m_rowsField;
	InputField m_colsField;
	InputField m_difficultyField;

	PopUp* m_popUp;
};