#pragma once

#include <iostream>
#include "defines.h"

using namespace std;

void errorUnknowParam(int line, string path);
void errorFontNotFound(string font);
void errorConfigNotFound(string file, int line, string path);
