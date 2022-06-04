#pragma once

#include "defines.h"

#include "Entity.h"
#include "Presenter.h"

class ConfigManager
{

public:
	ConfigManager();
	~ConfigManager();

	void load();
	void loadEntity();

	static Entity* m_enityModelPlayer1;
	static Entity* m_enityModelPlayer2;
	static Entity* m_enityModelEnemy;

private:

};
