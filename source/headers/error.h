#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <SDL2\SDL.h>
#include <time.h>
#include <fstream>

namespace Init
{
	void Init();
	void Deinit();
}

namespace Error
{
	//void PrintError(std::string _string);

	void Init();
}

#endif