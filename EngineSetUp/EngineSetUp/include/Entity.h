#pragma once

#include "defines.h"
#include "Presenter.h"

class Grid;

class Entity
{
public:

	Entity();
	
	Entity(const Entity* model, int2 squareIndex, int team);
	~Entity();

	static Grid* m_grid;

	void load(string entityName);

	void moveEntity(int2 coordinates);
	void scaleToGridSquare(int2 squareIndex);
	void draw();

	SDL_Rect getRect();

	// check if entity is from the same team as the one provided
	bool isFromTeam(int _team);

private:

	Drawable m_obj;

	gridSquare* m_taken;

	int m_team;		// 0 - no team, pos number - player, -1 - enemy
};
