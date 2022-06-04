#include "Validator.h"
#include "World.h"

extern World world;


bool canMove(int2 coor)
{
	return false;
}

bool isNumber(string data)
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

/*
* give all the squares that are unavailable after we places a queen
*/
vector<int2> giveUnavailableMoves(int2 coor, int rows, int colls)
{
	vector<int2> unavailableMoves; // return at the end of the function
	
	// king moves
	
	// curr place
	unavailableMoves.push_back(coor);
		
	for (int i = 0; i < 8; i++)
	{
		int2 buff = coor + directions[i];
		if (inGrid(buff, rows, colls))
		{
			unavailableMoves.push_back(buff);
		}
	}
	
	// now is time for the bishop and rook moves
	for (int i = 0; i < 8; i++)
	{
		lineMoves(coor, rows, colls, i, unavailableMoves);
	}

	return unavailableMoves;
}

/*
* gives all the moves in line (for bishop and rook) 
* @param coor - the current place of the piece
* @param rows - the number of rows
* @param colls - the number of columns
* @param _dir - the direction of the move
* @param out - the output vector
*/
void lineMoves(int2 coor, int rows, int colls, int _dir, vector<int2>& out)
{
	int2 offsetPerMove = directions[_dir];	// how much we move in each iteration

	int2 curr = coor + offsetPerMove;	// the current square we are on
	
	while (inGrid(curr, rows, colls))
	{
		out.push_back(curr);
		curr = curr + offsetPerMove;
	}
}

/*
* check if the move belongs to the grid
* @param coor - the move we want to check
* @param ROLLS - rows
* @param COLLS - colls
*/
bool inGrid(int2 coor, int ROWS, int COLLS)
{
	if (coor.x < 0 || coor.x >= ROWS || coor.y < 0 || coor.y >= COLLS)
	{
		return false;
	}
	return true;
}

