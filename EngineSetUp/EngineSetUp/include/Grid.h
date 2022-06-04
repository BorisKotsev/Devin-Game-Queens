#pragma once

#include "defines.h"
#include "Presenter.h"
#include <map>
#include "Entity.h"


/*
\brief Grid structure splitting a place into gridded squares
*/
class Grid
{
public:

	Grid();
	Grid(const Grid* model);
	~Grid();

	vector<vector<gridSquare>> m_gridSquares;

	void load();

	void update();
	void draw();

	void addEntity(int2 gridSquareIndex, int onTurn);
	
	int getSquareDimension();


private:
	
	Drawable m_gridBase;	// background of the grid
	Drawable m_gridBorder;  // border of the grid 
	Drawable m_possMove;	// possible to move square
	Drawable m_hover;		// the drawable for hovering

	gridSquare* m_hoverGrid;// the grid that we hover on

	int2 m_dimensions;		// shows the number of squares a grid has
	int	 m_squareDimension;	// shows what size the squares are

	int m_borderThickness;	// how thick is the border


	vector<Entity*> m_entities;
	Entity* m_currentEntity = nullptr;
	int2 m_lastEntityCoordinates;

	vector<gridSquare*> m_possibleMoves;

	int m_onTurn; // 0 - none, pos number - player, neg number - enemy

	void checkForClick();
	void onHover();

	void drawHover();
	void drawGridSquares();
	void drawEntities();
	void drawPossibleMoves();
	void calcPossibleMoves();
};