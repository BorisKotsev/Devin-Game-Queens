#include "Grid.h"

Grid::Grid()
{
}

Grid::~Grid()
{
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
}

void Grid::checkForClick()
{

}

void Grid::checkForHold()
{
}

void Grid::checkForRelease()
{
}

void Grid::createByGridSquareSize(int2 coordinates, int2 dimensions, int borderThickness, int squareSize, SDL_Texture* borderTexture, SDL_Texture* squareTexture)
{
	m_dimensions = dimensions;
	m_borderThickness = borderThickness;

	m_gridBase.rect = { coordinates.x, coordinates.y, dimensions.x* squareSize, dimensions.y * squareSize };
	
	m_gridBorder.rect = { m_gridBase.rect.x - borderThickness, m_gridBase.rect.y - borderThickness, m_gridBase.rect.w + 2*borderThickness, m_gridBase.rect.h + 2*borderThickness };
	m_gridBorder.texture = borderTexture;

	m_gridSquares.resize(dimensions.x);

	for (int r = 0; r < dimensions.x; r++)
	{
		m_gridSquares[r].resize(dimensions.y);

		for (int c = 0; c < dimensions.y; c++)
		{
			m_gridSquares[r][c].isFree = true;
			m_gridSquares[r][c].squareDrawable.rect = { r * squareSize + m_gridBase.rect.x, c * squareSize + m_gridBase.rect.y, squareSize, squareSize };
			m_gridSquares[r][c].squareDrawable.texture = squareTexture;
		}
	}

}

void Grid::update()
{
}
