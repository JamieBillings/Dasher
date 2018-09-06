/*==============================================================================
								Window Namespace
==============================================================================*/

namespace Window
{

void CreateWindow()
{
	window = SDL_CreateWindow("Dungeon",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		window_pos.w,
		window_pos.h, SDL_WINDOW_RESIZABLE);

	if(!window){
		printf("Error Creating Window\n");
	}
}

void DestroyWindow()
{
	SDL_DestroyWindow(window);
	window = nullptr;
}

}


/*==============================================================================
								Renderer Namespace
==============================================================================*/

namespace Renderer
{

void CreateRenderer()
{
	renderer = SDL_CreateRenderer(Window::window,
		-1,
		SDL_RENDERER_ACCELERATED);

	if(!renderer){
		printf("Error Creating Renderer\n");
	}
}

void ClearRenderer()
{
	SDL_GetWindowSize(Window::window,&Window::window_pos.w,&Window::window_pos.h);

	if(Window::window_pos.w < renderering_pos.w){
		SDL_SetWindowSize(Window::window, renderering_pos.w, Window::window_pos.h);
	}
	if(Window::window_pos.h < renderering_pos.h){
		SDL_SetWindowSize(Window::window, Window::window_pos.w, renderering_pos.h);
	}

	if((Window::window_pos.w > renderering_pos.w * (render_scale + 1)) &&
	 (Window::window_pos.h > renderering_pos.h * (render_scale + 1))){render_scale++;}

	if((Window::window_pos.w < renderering_pos.w * render_scale) ||
	 (Window::window_pos.h < renderering_pos.h * render_scale)){render_scale--;}

	Camrea::offset_x = (Window::window_pos.w / 2) - ((renderering_pos.w * render_scale) / 2);
	Camrea::offset_y = (Window::window_pos.h / 2) - ((renderering_pos.h * render_scale) / 2);

	SDL_SetRenderDrawColor(renderer, 71, 187, 255, 255);
	SDL_RenderClear(renderer);
}

void LineRender(SDL_Point _p1, SDL_Point _p2)
{
	SDL_Point new_point_1 = _p1;
	SDL_Point new_point_2 = _p2;

	new_point_1.x -= Camrea::offset_x;
	new_point_1.y -= Camrea::offset_y;
	new_point_2.x -= Camrea::offset_x;
	new_point_2.y -= Camrea::offset_y;

	SDL_RenderDrawLine(renderer, new_point_1.x, new_point_1.y,
		new_point_2.x, new_point_2.y);
}

void PresentRenderer()
{
	SDL_RenderPresent(renderer);
}

void DestroyRenderer()
{
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
}

}

/*=============================================================================
							CAMREA NAMESPACE
=============================================================================*/

namespace Camrea
{

	double set_x = 0;
	double set_y = 0;

	void RenderDebug()
	{
		SDL_Rect new_rect = BOUNDS;
		SDL_SetRenderDrawColor(Renderer::renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(Renderer::renderer, &new_rect);
		SDL_SetRenderDrawColor(Renderer::renderer, 0, 0, 0, 255);
	}

	void Update()
	{


	}
}