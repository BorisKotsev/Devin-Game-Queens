#include "Grid.h"

Grid::Grid()
{
}

Grid::~Grid()
{
}

void Grid::createByGridSize(int2 coordinates, int2 dimensions,int borderThickness ,int2 gridSize)
{
}

void Grid::createByGridSquareSize(int2 coordinates, int2 dimensions, int borderThickness, int squareSize)
{
	m_gridBase.rect = { coordinates.x, coordinates.y, dimensions.y* squareSize, dimensions.x * squareSize };
	m_gridBorder.rect = { m_gridBase.rect.x - borderThickness, m_gridBase.rect.y - borderThickness, m_gridBase.rect.w - borderThickness, m_gridBase.rect.h - borderThickness };

	m_gridSquares.resize(dimensions.y);

	for (int r = 0; r < dimensions.y; r++)
	{
		m_gridSquares[r].resize(dimensions.x);

		for (int c = 0; c < dimensions.x; c++)
		{
			m_gridSquares[r][c].isFree = true;
			m_gridSquares[r][c].squareDrawable.rect = { r * squareSize, c * squareSize, squareSize, squareSize };
		}
	}
}
