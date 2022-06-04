#pragma once

#include "defines.h"
#include "Presenter.h"
#include "Entity.h"
#include "Validator.h"
#include <map>


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

	void addEntity(int2 coor, int onTurn);
	
	int getSquareDimension();


private:
	
	Drawable m_gridBase;	// background of the grid
	Drawable m_gridBorder;  // border of the grid 
	Drawable m_possMove;	// possible to move square
	Drawable m_hover;		// the drawable for hovering

	SDL_Texture* m_oddSquareTexture;
	SDL_Texture* m_evenSquareTexture;

	gridSquare* m_hoverGrid;// the grid that we hover on

	int2 m_dimensions;		// shows the number of squares a grid has
	int	 m_squareDimension;	// shows what size the squares are

	int m_borderThickness;	// how thick is the border


	vector<Entity*> m_entities;
	Entity* m_currentEntity = nullptr;
	int2 m_lastEntityCoordinates;

	vector<gridSquare*> m_unavailableMoves;

	int m_onTurn; // 0 - none, pos number - player, neg number - enemy

	void checkForClick();
	void onHover();

	void drawHover();
	void drawGridSquares();
	void drawEntities();
	void drawUnavailableMoves();
	void calcUnavailableMoves();

	bool possMove(int2 coor);
};