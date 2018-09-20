#include "headers\\_error.h"
#include "headers\\_timer.h"
#include "headers\\_rendering.h"
#include "headers\\_texture.h"
#include "headers\\_font.h"
#include "headers\\_tools.h"
#include "headers\\entity.h"
#include "headers\\game.h"

#include "_error.cpp"
#include "_timer.cpp"
#include "_rendering.cpp"
#include "_texture.cpp"
#include "_font.cpp"
#include "_tools.cpp"
#include "entity.cpp"
#include "game.cpp"

bool running = true;
SDL_Event event;

int main (int _argc, char* _argv[])
{
	Game::Init();

	while(running){
		Timer::frequency = static_cast<float>(SDL_GetPerformanceFrequency());
		running = Game::Event(&event);
		Game::GameLoop();

		SDL_SetRenderDrawColor(Renderer::renderer, 0, 0, 0, 255);
		Renderer::ClearRenderer();
		Game::Render();
		Renderer::PresentRenderer();

		Timer::CapFramerate();
	}

	Game::Destroy();

	return 0;
}