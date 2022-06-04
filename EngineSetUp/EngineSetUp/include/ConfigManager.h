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
	void loadInvalidInputMsg();

	static Entity* m_enityModel;
	static Drawable* m_invalidInputMsg;

private:

};
