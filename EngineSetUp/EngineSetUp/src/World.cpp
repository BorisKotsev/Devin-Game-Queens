#include "World.h"

World::World()
{
}

World::~World()
{
}

void World::init()
{
	m_presenter.init();

	m_stateManager.init(GAME_STATE::TITLE_SCREEN);
}

void World::run()
{
	m_inputManager.handleInput();

	m_stateManager.run();

	m_presenter.draw();
}

// call destroy for all classes to prevent memory leak
void World::destroy()
{
}

bool World::isRunning()
{
	return m_isRunning;
}
