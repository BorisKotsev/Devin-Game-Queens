#pragma once

#include "defines.h"

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
};

class ConfigManager
{

public:
	ConfigManager();
	~ConfigManager();

	void load();
	void loadGrid();

	GridModel m_gridModel;

private:

};
