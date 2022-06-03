#include "Validator.h"
#include "World.h"

extern World world;

Validator::Validator()
{

}

Validator::~Validator()
{
	
}

bool Validator::canMove(int2 coor)
{
	return false;
}

bool Validator::isNumber(string data)
{
	for (int i = 0; i < data.length(); i++)
	{
		if (!isdigit(data[i]))
		{
			return false;
		}
	}

	return true;
}
