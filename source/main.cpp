#include "headers\\error.h"
#include "headers\\timer.h"
#include "headers\\rendering.h"
#include "headers\\texture.h"
#include "headers\\font.h"
#include "headers\\tools.h"
#include "headers\\game.h"

#include "error.cpp"
#include "timer.cpp"
#include "rendering.cpp"
#include "texture.cpp"
#include "font.cpp"
#include "tools.cpp"
#include "game.cpp"

bool running = true;
SDL_Event event;

int main (int _argc, char* _argv[])
{
	Game::Init();

	while(running){

		running = Game::Event(&event);

		int x,y;
		SDL_GetMouseState(&x,&y);

		
		Game::Render();


	}

	Game::Destroy();

	return 0;
}