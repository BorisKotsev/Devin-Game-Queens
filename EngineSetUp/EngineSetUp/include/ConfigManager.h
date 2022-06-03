#pragma once

#include "defines.h"

#include "Entity.h"
#include "Presenter.h"

struct GridModel
{
	int2 coordinates;
	int2 dimensions;
	int squareSize;
	int borderThickness;
	
	SDL_Texture* borderTexture;
	SDL_Texture* baseTexture;
	SDL_Texture* squareTexture;
	SDL_Texture* canMove;
};

class ConfigManager
{

public:
	ConfigManager();
	~ConfigManager();

	void load();
	void loadEntity();

	GridModel m_gridModel;
	static Entity* m_enityModel;

private:

};
