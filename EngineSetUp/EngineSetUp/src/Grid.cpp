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
	int squareSize;
	int borderThickness;

	string temp;
	fstream stream;

	stream.open(CONFIG_FOLDER + "game\\grid.txt");

	stream >> temp >> coordinates.x >> coordinates.y;
	stream >> temp >> m_dimensions.y >> m_dimensions.x;
	stream >> temp >> squareSize;
	stream >> temp >> borderThickness;

	stream.close();

	m_gridBorder.texture = loadTexture("game\\gridBorderTexture.bmp");
	m_gridBase.texture = loadTexture("game\\gridSquareTexture.bmp");
	m_possMove.texture = loadTexture("game\\gridPossMove.bmp");
	m_hover.texture = loadTexture("game\\gridPossMove.bmp");

	m_gridBase.rect = { coordinates.x, coordinates.y, m_dimensions.x * squareSize, m_dimensions.y * squareSize };
	m_gridBorder.rect = 
	{	m_gridBase.rect.x - borderThickness, 
		m_gridBase.rect.y - borderThickness, 
		m_gridBase.rect.w + 2 * borderThickness, 
		m_gridBase.rect.h + 2 * borderThickness };

	m_gridSquares.resize(m_dimensions.x);
	
	for (int r = 0; r < m_dimensions.x; r++)
	{
		m_gridSquares[r].resize(m_dimensions.y);
		
		for (int c = 0; c < m_dimensions.y; c++)
		{
			m_gridSquares[r][c].isFree = true;
			m_gridSquares[r][c].squareDrawable.rect = { r * squareSize + m_gridBase.rect.x, c * squareSize + m_gridBase.rect.y, squareSize, squareSize };
			m_gridSquares[r][c].squareDrawable.texture = m_gridBase.texture;
		}
	}
}

void Grid::draw()
{
	drawObject(m_gridBorder);

	for (int r = 0; r < m_dimensions.x; r++)
	{
		for (int c = 0; c < m_dimensions.y; c++)
		{
			drawObject(m_gridSquares[r][c].squareDrawable);
		}
	}
	
	drawPossibleMoves();

	drawHover();
}

void Grid::checkForClick()
{
	if (world.m_inputManager.m_mouseOnClick)
	{
		for (int r = 0; r < m_dimensions.x; r++)
		{
			for (int c = 0; c < m_dimensions.y; c++)
			{
				if (MouseIsInRect(world.m_inputManager.m_mouseCoor, m_gridSquares[r][c].squareDrawable.rect))
				{
					cout << "Clicked on " << r << " " << c << endl;
				}
			}
		}
	}
}

void Grid::checkForHold()
{
	if (world.m_inputManager.m_drag)
	{
		// we drag with the mouse
	}
}	

void Grid::checkForRelease()
{
	if (world.m_inputManager.m_mouseOnRelease)
	{
		// we release the mouse
	}
}

void Grid::onHover()
{
	m_hoverGrid = nullptr;
	for (int r = 0; r < m_dimensions.x; r++)
	{
		for (int c = 0; c < m_dimensions.y; c++)
		{
			if (MouseIsInRect(world.m_inputManager.m_mouseCoor, m_gridSquares[r][c].squareDrawable.rect))
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
		m_hover.rect = m_hoverGrid->squareDrawable.rect;
		drawObject(m_hover);
	}
}

void Grid::drawPossibleMoves()
{
	for(gridSquare* gs : m_possibleMoves)
	{
		m_possMove.rect = gs->squareDrawable.rect;
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

	checkForHold();

	calcPossibleMoves();
}
