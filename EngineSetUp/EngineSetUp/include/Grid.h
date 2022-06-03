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
	Grid(const Grid* model);
	~Grid();

	void load();

	void update();
	void draw();

private:
	
	Drawable m_gridBase;	// background of the grid
	Drawable m_gridBorder;  // border of the grid 
	Drawable m_possMove;	// possible to move square
	Drawable m_hover;		// the drawable 

	gridSquare* m_hoverGrid;// the grid that we hover on

	int2 m_dimensions;		// shows the number of squares a grid has
	int2 m_squareDimension;	// shows what size the squares are

	int m_borderThickness;	// how thick is the border

	vector<vector<gridSquare>> m_gridSquares;

	vector<Entity> m_entities;

	vector<gridSquare*> m_possibleMoves;

	void checkForClick();
	void checkForHold();
	void checkForRelease();
	void onHover();

	void drawHover();
	void drawPossibleMoves();
	void calcPossibleMoves();
};