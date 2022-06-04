#include "Entity.h"

#include "Grid.h"

Grid* Entity::m_grid = nullptr;

Entity::Entity()
{
	m_team = 0; // unasigned at the begining
}

Entity::Entity(const Entity* model, int2 squareIndex, int team)
{
	m_obj.rect.w = m_grid->getSquareDimension();
	m_obj.rect.h = m_grid->getSquareDimension();

	m_obj.rect.x = model->m_grid->m_gridSquares[squareIndex.x][squareIndex.y].rect.x;
	m_obj.rect.y = model->m_grid->m_gridSquares[squareIndex.x][squareIndex.y].rect.y;
	
	m_taken = &model->m_grid->m_gridSquares[squareIndex.x][squareIndex.y];

	m_obj.texture = model->m_obj.texture;

	m_team = team;
}

Entity::~Entity()
{
}

void Entity::load(string entityName)
{
	m_obj.texture = loadTexture("game\\" + entityName + ".bmp");

}

void Entity::moveEntity(int2 coordinates)
{
	m_obj.rect.x = coordinates.x - m_obj.rect.w/2;
	m_obj.rect.y = coordinates.y - m_obj.rect.h/2;
}

void Entity::scaleToGridSquare(int2 squareIndex)
{
	m_obj.rect.x = m_grid->m_gridSquares[squareIndex.x][squareIndex.y].rect.x;
	m_obj.rect.y = m_grid->m_gridSquares[squareIndex.x][squareIndex.y].rect.y;
	
	m_taken = &m_grid->m_gridSquares[squareIndex.x][squareIndex.y];
}

void Entity::draw()
{
	drawObject(m_obj);

}

SDL_Rect Entity::getRect()
{
	return m_obj.rect;
}

/*
* @param _team - the team that we want to check
*/
bool Entity::isFromTeam(int _team)
{
	return m_team == _team;
}
