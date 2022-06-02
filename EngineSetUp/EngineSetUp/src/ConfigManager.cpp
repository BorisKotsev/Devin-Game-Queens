#include "ConfigManager.h"
#include "World.h"

ConfigManager::ConfigManager()
{
}

ConfigManager::~ConfigManager()
{
}

void ConfigManager::load()
{
	loadGrid();
}

void ConfigManager::loadGrid()
{

	string temp;
	fstream stream;

	stream.open(CONFIG_FOLDER + "game\\grid.txt");

	stream >> temp >> m_gridModel.coordinates.x >> m_gridModel.coordinates.y;
	stream >> temp >> m_gridModel.dimensions.y >> m_gridModel.dimensions.x;
	stream >> temp >> m_gridModel.squareSize;
	stream >> temp >> m_gridModel.borderThickness;

	stream.close();

	m_gridModel.borderTexture = loadTexture("game\\gridBorderTexture.bmp");
	m_gridModel.squareTexture = loadTexture("game\\gridSquareTexture.bmp");
}
