#include "headers\\error.h"
#include "headers\\timer.h"
#include "headers\\rendering.h"
#include "headers\\texture.h"
#include "headers\\font.h"
#include "headers\\tools.h"

#include "error.cpp"
#include "timer.cpp"
#include "rendering.cpp"
#include "texture.cpp"
#include "font.cpp"
#include "tools.cpp"

bool running = true;

int main (int _argc, char* _argv[])
{
	Init::Init();

	Window::CreateWindow();
	Renderer::CreateRenderer();

	while(running){
		int x,y;
		SDL_GetMouseState(&x,&y);

		int line_x = 100;
		int line_y = 100;
		int line_x_2 = 300;
		int line_y_2 = 300;

		SDL_SetRenderDrawColor(Renderer::renderer, 0, 0, 0, 255);
		Renderer::ClearRenderer();

		SDL_SetRenderDrawColor(Renderer::renderer, 0, 255, 0, 255);

		Renderer::PresentRenderer();


	}

	Renderer::DestroyRenderer();
	Window::DestroyWindow();

	return 0;
}