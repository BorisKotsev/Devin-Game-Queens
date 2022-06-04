#pragma once

#include "defines.h"
#include "Presenter.h"
#include "Entity.h"
#include "Validator.h"
#include <map>
#include <limits>


struct AI_move
{
	int2 coordinates;
	int efficiency;
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

	int2 m_dimensions;		// shows the number of squares a grid has
	int m_winner = 0;		// shows the winner of the game

	vector<vector<gridSquare>> m_gridSquares;

	void load(int opponent);

	void update();
	void draw();

	void addEntity(int2 coor, int onTurn);
	void winCondition();
	
	void destroy();

	int getSquareDimension();

	int2 easyBot(vector<vector<gridSquare>> matrix);			// returns the AI decision of coordinates to place the new entity
	int2 mediumBot(vector<vector<gridSquare>> matrix);
	
	bool checkForPossibleWin(vector<vector<gridSquare>> matrix);
	
private:
	
	Drawable m_player1OnTurn;
	Drawable m_player2OnTurn;
	Drawable m_tutorial;
	
	int m_opponent = 0;		// against who are we playing

	Drawable m_gridBase;	// background of the grid
	Drawable m_gridBorder;  // border of the grid 
	Drawable m_unavailableMove;	// possible to move square
	Drawable m_hover;		// the drawable for hovering

	SDL_Texture* m_oddSquareTexture;
	SDL_Texture* m_evenSquareTexture;

	gridSquare* m_hoverGrid;// the grid that we hover on

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

	bool m_drawTutorial;
};