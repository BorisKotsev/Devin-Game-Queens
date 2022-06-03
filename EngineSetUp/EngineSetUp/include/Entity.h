#pragma once

#include "defines.h"
#include "Presenter.h"

class Grid;

class Entity
{
public:

	Entity();
	
	Entity(const Entity* model, int2 squareIndex);
	~Entity();

	static Grid* m_grid;

	void load(string entityName);

	void moveEntity(int2 coordinates);
	void scaleToGridSquare(int2 squareIndex);
	void draw();

	SDL_Rect getRect();

private:

	Drawable m_obj;

	gridSquare* m_taken;

};
