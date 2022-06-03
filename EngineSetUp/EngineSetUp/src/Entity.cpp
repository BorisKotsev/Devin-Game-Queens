#include "Entity.h"

#include "Grid.h"

Grid* Entity::m_grid = nullptr;

Entity::Entity()
{
}

Entity::Entity(const Entity* model, int2 squareIndex)
{
	
	D(m_grid->getSquareDimension());

	m_obj.rect.w = m_grid->getSquareDimension();
	m_obj.rect.h = m_grid->getSquareDimension();

	m_obj.rect.x = model->m_grid->m_gridSquares[squareIndex.x][squareIndex.y].rect.x;
	m_obj.rect.y = model->m_grid->m_gridSquares[squareIndex.x][squareIndex.y].rect.y;
	
	m_taken = &model->m_grid->m_gridSquares[squareIndex.x][squareIndex.y];

	m_obj.texture = model->m_obj.texture;
	
}

Entity::~Entity()
{
}

void Entity::load(string entityName)
{
	m_obj.texture = loadTexture("game\\" + entityName + "Texture.bmp");

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
