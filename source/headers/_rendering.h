#ifndef RENDERING_INCLUDED_H
#define RENDERING_INCLUDED_H

namespace Window
{
	SDL_Window* window;
	SDL_Rect window_pos = {0,0,640,480};
	
	void CreateWindow();
	void DestroyWindow();

}

namespace Renderer
{
	SDL_Renderer* renderer;
	SDL_Rect renderering_pos = {0,0,640,480};
	int render_scale = 1;

	void CreateRenderer();
	void ClearRenderer();
	void PresentRenderer();
	void LineRender(SDL_Point _p1, SDL_Point _p2);
	void DestroyRenderer();
}

namespace Camrea
{
	double offset_x = 0;
	double offset_y = 0;

	const SDL_Rect BOUNDS = {247,167,147,147};
	SDL_Rect game_camrea = {0,0,640,480};
	void RenderDebug();
	void Update();
}



#endif