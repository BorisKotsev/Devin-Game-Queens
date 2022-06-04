#include "Grid.h"

#include "World.h"

extern World world;

Grid::Grid()
{
	m_hoverGrid = nullptr;
}

Grid::Grid(const Grid* model)
{
	m_dimensions = model->m_dimensions;
	m_borderThickness = model->m_borderThickness;

	m_gridBase.rect = model->m_gridBase.rect;

	m_gridBorder.rect = model->m_gridBorder.rect;
	m_gridBorder.texture = model->m_gridBorder.texture;

	m_gridSquares = model->m_gridSquares;
}

Grid::~Grid()
{
}

void Grid::load()
{
	int2 coordinates;

	string temp;
	fstream stream;

	stream.open(CONFIG_FOLDER + "game\\grid.txt");

	stream >> temp >> coordinates.x >> coordinates.y;
	stream >> temp >> m_dimensions.x >> m_dimensions.y;
	stream >> temp >> m_squareDimension;
	stream >> temp >> m_borderThickness;

	stream.close();

	m_gridBorder.texture = loadTexture("game\\gridBorderTexture.bmp");
	m_gridBase.texture = loadTexture("game\\gridSquareTexture.bmp");
	m_possMove.texture = loadTexture("game\\gridPossMove.bmp");
	m_hover.texture = loadTexture("game\\gridPossMove.bmp");

	m_gridBase.rect = { coordinates.x, coordinates.y, m_dimensions.y * m_squareDimension, m_dimensions.x * m_squareDimension };

	m_gridBorder.rect = 
	{	m_gridBase.rect.x - m_borderThickness, 
		m_gridBase.rect.y - m_borderThickness, 
		m_gridBase.rect.w + 2 * m_borderThickness, 
		m_gridBase.rect.h + 2 * m_borderThickness };

	m_gridSquares.resize(m_dimensions.y);
	
	for (int r = 0; r < m_dimensions.y; r++)
	{
		m_gridSquares[r].resize(m_dimensions.x);
		
		for (int c = 0; c < m_dimensions.x; c++)
		{
			m_gridSquares[r][c].isFree = true;
			m_gridSquares[r][c].rect = { r * m_squareDimension + m_gridBase.rect.x, c * m_squareDimension + m_gridBase.rect.y, m_squareDimension, m_squareDimension };
			m_gridSquares[r][c].texture = m_gridBase.texture;
		}
	}
}

void Grid::draw()
{
	drawObject(m_gridBorder);

	drawGridSquares();

	drawEntities();

	drawPossibleMoves();

	drawHover();
}

void Grid::addEntity(int2 gridSquareIndex, int onTurn)
{
	Entity* temp = new Entity(ConfigManager::m_enityModel, gridSquareIndex, onTurn);
	m_entities.push_back(temp);
}

int Grid::getSquareDimension()
{
	return m_squareDimension;
}

void Grid::checkForClick()
{
	if (world.m_inputManager.m_mouseOnClick)
	{
		for (int r = 0; r < m_dimensions.x; r++)
		{
			for (int c = 0; c < m_dimensions.y; c++)
			{
				if (MouseIsInRect(world.m_inputManager.m_mouseCoor, m_gridSquares[r][c].rect))
				{
					int2 coor;
					coor.x = r;
					coor.y = c;
					
					addEntity(coor, m_onTurn);
				}
			}
		}
		for (int i = 0; i < m_entities.size(); i++)
		{
			if (MouseIsInRect(world.m_inputManager.m_mouseCoor, m_entities[i]->getRect()))
			{
				m_currentEntity = m_entities[i];
				m_lastEntityCoordinates = centerOfRect(m_entities[i]->getRect());
			}
		}
	}
}

void Grid::drawGridSquares()
{
	for (int r = 0; r < m_dimensions.x; r++)
	{
		for (int c = 0; c < m_dimensions.y; c++)
		{
			drawObject(m_gridSquares[r][c]);
		}
	}

}

void Grid::drawEntities()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		m_entities[i]->draw();
	}
}

void Grid::onHover()
{
	m_hoverGrid = nullptr;
	for (int r = 0; r < m_dimensions.x; r++)
	{
		for (int c = 0; c < m_dimensions.y; c++)
		{
			if (MouseIsInRect(world.m_inputManager.m_mouseCoor, m_gridSquares[r][c].rect))
			{
				m_hoverGrid = &m_gridSquares[r][c];
			}
		}
	}
}

void Grid::drawHover()
{
	if (m_hoverGrid != nullptr)
	{
		m_hover.rect = m_hoverGrid->rect;
		drawObject(m_hover);
	}
}

void Grid::drawPossibleMoves()
{
	for(gridSquare* gs : m_possibleMoves)
	{
		m_possMove.rect = gs->rect;
		drawObject(m_possMove);
	}
}

void Grid::calcPossibleMoves()
{
	m_possibleMoves.clear();
	for (int r = 0; r < m_dimensions.x; r++)
	{
		for (int c = 0; c < m_dimensions.y; c++)
		{
			// just some rand shit
			if (c % 2 == 0 && r % 2 == 0) m_possibleMoves.push_back(&m_gridSquares[r][c]);
		}
	}
}

void Grid::update()
{
	onHover();

	checkForClick();

	calcPossibleMoves();
}
