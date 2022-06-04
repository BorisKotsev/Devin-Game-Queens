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

	static Entity* m_enityModel;

private:

};
