#pragma once

#include "defines.h"
#include <map>

struct gridSquare
{
	Drawable squareDrawable;
	bool isFree;
};

/*
\brief Grid structure splitting a place into gridded squares
*/
class Grid
{
public:

	Grid();
	~Grid();

	void createByGridSize(int2 coordinates,int2 dimensions,int borderThickness ,int2 gridSize);
	void createByGridSquareSize(int2 coordinates,int2 dimensions,int borderThickness, int squareSize);

private:

	Drawable m_gridBase;	// background of the grid
	Drawable m_gridBorder;  // border of the grid
	
	int2 dimensions;		// shows the number of squares a grid has
	int2 squareDimension;	// shows what size the squares are

	int m_borderThickness;	// how thick is the border

	vector<vector<gridSquare>> m_gridSquares;

};