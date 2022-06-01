#pragma once

#include "defines.h"
#include "Presenter.h"

class Entity
{
public:
	Entity();
	~Entity();

	void SetEntity();

private:

	Drawable m_obj;

};
