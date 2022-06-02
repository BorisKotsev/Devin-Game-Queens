#pragma once

#include "defines.h"
#include "Presenter.h"
#include <map>
#include "Entity.h"

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

	void createByGridSquareSize(int2 coordinates,int2 dimensions,int borderThickness, int squareSize, SDL_Texture* borderTexture, SDL_Texture* squareTexture);
	void update();
	void draw();


private:

	Drawable m_gridBase;	// background of the grid
	Drawable m_gridBorder;  // border of the grid
	
	int2 m_dimensions;		// shows the number of squares a grid has
	int2 m_squareDimension;	// shows what size the squares are

	int m_borderThickness;	// how thick is the border

	vector<vector<gridSquare>> m_gridSquares;

	vector<Entity> m_entities;

	void checkForClick();
	void checkForHold();
	void checkForRelease();
};