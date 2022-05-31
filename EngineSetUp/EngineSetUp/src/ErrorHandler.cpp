#include "ErrorHandler.h"

void errorUnknowParam(int line, string path)
{
	cout << "Error: Entering a value to an unknow parameter in " << path << "|" << line << endl;

	SDL_Delay(50000);
}

void errorFontNotFound(string font)
{
	cout << "Error: Font not found " << font << endl;

	SDL_Delay(50000);
}

void errorConfigNotFound(string file, int line, string path)
{
	cout << "Error: File not found in path " << file << " in file " << path << "|" << line << endl;

	SDL_Delay(50000);
}
