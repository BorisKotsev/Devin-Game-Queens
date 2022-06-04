#include "Grid.h"

#include "World.h"

extern World world;

Grid::Grid()
{
	m_hoverGrid = nullptr;
	m_onTurn = 1;
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

void Grid::load(int opponent)
{
	m_opponent = opponent;

	int2 coordinates;

	string temp;
	fstream stream;

	stream.open(CONFIG_FOLDER + GAME_FOLDER + "grid.txt");

	stream >> temp >> coordinates.x >> coordinates.y;
	stream >> temp >> m_squareDimension;
	stream >> temp >> m_borderThickness;

	stream.close();
	
	m_gridBorder.texture = loadTexture(GAME_FOLDER + "gridBorderTexture.bmp");
	m_unavailableMove.texture = loadTexture(GAME_FOLDER + "unavailableTile.bmp");
	m_hover.texture = loadTexture(GAME_FOLDER + "gridPossMove.bmp");

	m_oddSquareTexture = loadTexture(GAME_FOLDER + "gridOddSquareTexture.bmp");
	m_evenSquareTexture = loadTexture(GAME_FOLDER + "gridEvenSquareTexture.bmp");

	m_gridBase.rect = { coordinates.x, coordinates.y, m_dimensions.y * m_squareDimension, m_dimensions.x * m_squareDimension };

	m_gridBorder.rect = 
	{	
		m_gridBase.rect.x - m_borderThickness, 
		m_gridBase.rect.y - m_borderThickness, 
		m_gridBase.rect.w + 2 * m_borderThickness, 
		m_gridBase.rect.h + 2 * m_borderThickness 
	};

	m_gridSquares.resize(m_dimensions.x);
	
		
	for (int r = 0; r < m_gridSquares.size(); r++)
	{
		m_gridSquares[r].resize(m_dimensions.y);
		
		for (int c = 0; c < m_gridSquares[r].size(); c++)
		{
			m_gridSquares[r][c].isFree = true;
			m_gridSquares[r][c].rect = { c * m_squareDimension + m_gridBase.rect.x, r * m_squareDimension + m_gridBase.rect.y, m_squareDimension, m_squareDimension };
			
			if (r % 2 == 0)
			{
				if (c % 2 == 0)
				{
					m_gridSquares[r][c].texture = m_evenSquareTexture;
				}
				else
				{
					m_gridSquares[r][c].texture = m_oddSquareTexture;
				}
			}
			else
			{
				if (c % 2 == 0)
				{
					m_gridSquares[r][c].texture = m_oddSquareTexture;
				}
				else
				{
					m_gridSquares[r][c].texture = m_evenSquareTexture;
				}
			}
		}
	}
	
	cout << "GRID SIZE ROWS " << m_gridSquares.size() << " COLLS " << m_gridSquares[0].size();

}

void Grid::draw()
{
	drawObject(m_gridBorder);

	drawGridSquares();

	drawUnavailableMoves();

	drawEntities();

	drawHover();
}
/*
* used when we want to add an entity
* @param coor - where we want to add an entity (rows, colls)
* @param onTurn - the curr player
*/
void Grid::addEntity(int2 coor, int onTurn)
{
	if (possMove(coor))
	{
		Entity* temp;
		switch (onTurn)
		{
		case 1:
			temp = new Entity(ConfigManager::m_enityModelPlayer1, coor, onTurn);
			break;
		case 2:
			temp = new Entity(ConfigManager::m_enityModelPlayer2, coor, onTurn);
			break;
		case -1:
			temp = new Entity(ConfigManager::m_enityModelEnemy, coor, onTurn);
			break;
		case -2:
			temp = new Entity(ConfigManager::m_enityModelEnemy, coor, onTurn);
			break;
		default:
			break;
		}
		m_entities.push_back(temp);
		
		vector<int2> buff = giveUnavailableMoves(coor, m_dimensions.x, m_dimensions.y);

		for(int i = 0; i < buff.size(); i++)
		{
			cout << "r: " << buff[i].x << " c: " << buff[i].y << endl;
			m_gridSquares[buff[i].x][buff[i].y].isFree = false;
		}

		m_onTurn = (m_onTurn == m_opponent) ? 1 : m_opponent;
		
	}
	else
	{
		cout << "Invalid move" << endl;
	}
}

int Grid::getSquareDimension()
{
	return m_squareDimension;
}

int2 Grid::easyBot(vector<vector<gridSquare>> m_matrix)
{
	vector<int2> freeSquares;

	for (int i = 0; i < m_matrix.size(); i++)
	{
		for (int j = 0; j < m_matrix[i].size(); j++)
		{
			if (m_matrix[i][j].isFree)
			{
				freeSquares.push_back(int2{i,j});
			}
		}
	}
	
	int randomIndex = 0 + rand() % freeSquares.size();

	return freeSquares[randomIndex];
}

int2 Grid::mediumBot(vector<vector<gridSquare>> m_matrix)
{
	// decide how many moves into the future to check
	int moves = 1;


	return playFutureMoves(m_matrix, moves, 1).coordinates;
}

AI_move Grid::playFutureMoves(vector<vector<gridSquare>> matrix, int movesIntoTheFuture, int isMyTurn)
{
	vector<int2> possibleMoves;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j].isFree)
			{
				possibleMoves.push_back(int2{ i,j });
			}
		}
	}   
	// gets possible moves indexes

	if (movesIntoTheFuture == 0)
	{
		AI_move temp;
		temp.efficiency = possibleMoves.size();
		return temp;
	}

	AI_move bestMove;
	bestMove.efficiency = m_gridSquares.size() * m_gridSquares[0].size();
	AI_move temp;

	for (int i = 0; i < possibleMoves.size(); i++)
	{
		vector<vector<gridSquare>> newMoveMatrix;
		vector<int2> unavailable = giveUnavailableMoves(possibleMoves[i], matrix.size(), matrix[0].size());

		for (int i = 0; i < unavailable.size(); i++)
		{
			newMoveMatrix[unavailable[i].x][unavailable[i].y].isFree = false;
		}

		temp = playFutureMoves(newMoveMatrix, movesIntoTheFuture--, isMyTurn * (-1));	// gets efficiency
		temp.coordinates = possibleMoves[i];											// gets coordinates

		if (temp.efficiency != 0)						// get the more efficient move			
		{
			if (temp.efficiency < bestMove.efficiency)
			{
				bestMove.coordinates = temp.coordinates;
				bestMove.efficiency = temp.efficiency;
			}
		}
		else if (temp.efficiency == 0 && isMyTurn == -1) // player win con -> skip and forget this move
		{

		}
		else if (temp.efficiency == 0 && isMyTurn == 0) // bot win con -> very good move
		{
			bestMove = temp;
		}

	}

	return bestMove;
}

void Grid::getFutureUnavailableMoves(vector<vector<gridSquare>>& matrix, int2 coor)
{
}


void Grid::checkForClick()
{
	if (world.m_inputManager.m_mouseOnClick)
	{
		for (int r = 0; r < m_gridSquares.size(); r++)
		{
			for (int c = 0; c < m_gridSquares[r].size(); c++)
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
	for (int r = 0; r < m_gridSquares.size(); r++)
	{
		for (int c = 0; c < m_gridSquares[r].size(); c++)
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
	for (int r = 0; r < m_gridSquares.size(); r++)
	{
		for (int c = 0; c < m_gridSquares[r].size(); c++)
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

void Grid::drawUnavailableMoves()
{
	for(gridSquare* gs : m_unavailableMoves)
	{
		m_unavailableMove.rect = gs->rect;
		drawObject(m_unavailableMove);
	}
}

void Grid::calcUnavailableMoves()
{
	m_unavailableMoves.clear();
	for (int r = 0; r < m_gridSquares.size(); r++)
	{
		for (int c = 0; c < m_gridSquares[r].size(); c++)
		{
			if (m_gridSquares[r][c].isFree == false)
			{
				m_unavailableMoves.push_back(&m_gridSquares[r][c]);
			}
		}
	}
}

/*
* check for valid move when we add entity
* @param coor - the coordinates of the square we are checking
* @return true if the square is free, false if it is not
*/
bool Grid::possMove(int2 coor)
{
	if (inGrid(coor, m_dimensions.x, m_dimensions.y))
	{
		if (m_gridSquares[coor.x][coor.y].isFree)
		{
			return true;
		}
	}
	return false;
}

void Grid::update()
{
	onHover();

	if (m_onTurn == -1)
	{
		SDL_Delay(2000);
		addEntity(easyBot(m_gridSquares), m_onTurn);
	}
	else if (m_onTurn == -2)
	{
		//addEntity(mediumBot(m_gridSquares), m_onTurn);
	}
	else
	{
		checkForClick();
	}
	calcUnavailableMoves();
}
