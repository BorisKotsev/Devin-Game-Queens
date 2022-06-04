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

	string temp;
	fstream stream;

	stream.open(CONFIG_FOLDER + "game\\grid.txt");

	stream >> temp >> coordinates.x >> coordinates.y;
	stream >> temp >> m_dimensions.x >> m_dimensions.y;
	stream >> temp >> m_squareDimension;
	stream >> temp >> m_borderThickness;

	stream.close();

	m_gridBorder.texture = loadTexture("game\\gridBorderTexture.bmp");
	m_possMove.texture = loadTexture("game\\gridPossMove.bmp");
	m_hover.texture = loadTexture("game\\gridPossMove.bmp");

	m_oddSquareTexture = loadTexture("game\\gridOddSquareTexture.bmp");
	m_evenSquareTexture = loadTexture("game\\gridEvenSquareTexture.bmp");

	m_gridBase.rect = { coordinates.x, coordinates.y, m_dimensions.y * m_squareDimension, m_dimensions.x * m_squareDimension };

	m_gridBorder.rect = 
	{	m_gridBase.rect.x - m_borderThickness, 
		m_gridBase.rect.y - m_borderThickness, 
		m_gridBase.rect.w + 2 * m_borderThickness, 
		m_gridBase.rect.h + 2 * m_borderThickness };

	m_gridSquares.resize(m_dimensions.y);
	
	for (int r = 0; r < m_gridSquares.size(); r++)
	{
		m_gridSquares[r].resize(m_dimensions.x);
		
		for (int c = 0; c < m_gridSquares[r].size(); c++)
		{
			m_gridSquares[r][c].isFree = true;
			m_gridSquares[r][c].rect = { r * m_squareDimension + m_gridBase.rect.x, c * m_squareDimension + m_gridBase.rect.y, m_squareDimension, m_squareDimension };

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
}

void Grid::draw()
{
	drawObject(m_gridBorder);

	drawGridSquares();

	drawEntities();

	//drawPossibleMoves();

	drawHover();
}

void Grid::addEntity(int2 gridSquareIndex, int onTurn)
{

	Entity* temp = new Entity(ConfigManager::m_enityModel, gridSquareIndex, onTurn);
	m_entities.push_back(temp);
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
	
	int newCoord = 0 + rand() % freeSquares.size();

	return int2{ freeSquares[newCoord].x, freeSquares[newCoord].y };
}

int2 Grid::mediumBot(vector<vector<gridSquare>> m_matrix)
{
	// decide how many moves into the future to check
	int moves = 1;

	return playFutureMoves(m_matrix, moves).coordinates;
}

AI_move Grid::playFutureMoves(vector<vector<gridSquare>> m_matrix, int movesIntoTheFuture)
{
	// play a move - save how efficient it was
	// reduce free Squares

	/*
	if (movesIntoTheFuture == 0)
	{
		AI_move temp;

		if ( == 0)
		{
			temp.efficiency = m_gridSquares.size() * m_gridSquares[0].size();
			return temp;
		}
		else
		{
			temp.efficiency = freeSquares.size();
			return temp;
		}
	}
	else
	{
		AI_move bestMove;
		bestMove.efficiency = -1;
		
		for (int i = 0; i < freeSquares.size(); i++)
		{
			vector<int2> futureFreeSquares;
			futureFreeSquares = freeSquares;
			futureFreeSquares.erase(futureFreeSquares.begin() + i);

			AI_move tempMove = playFutureMoves(futureFreeSquares, movesIntoTheFuture--);

			if (bestMove.efficiency < tempMove.efficiency)
			{
				bestMove.coordinates = freeSquares[i];
				bestMove.efficiency = tempMove.efficiency;
			}
		}

		return bestMove;
	}
	*/
	return AI_move();
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

void Grid::drawPossibleMoves()
{
	for(gridSquare* gs : m_possibleMoves)
	{
		m_possMove.rect = gs->rect;
		drawObject(m_possMove);
	}
}

void Grid::calcPossibleMoves()
{
	m_possibleMoves.clear();
	for (int r = 0; r < m_gridSquares.size(); r++)
	{
		for (int c = 0; c < m_gridSquares[r].size(); c++)
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

	calcPossibleMoves();
}
