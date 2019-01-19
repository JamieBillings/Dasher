namespace T_Renderer
{


void Create()
{
    renderer = SDL_CreateRenderer(T_Window::window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == nullptr){
        OS::CreateErrorWindow("Could not Create Renderer", error_level::error);
    }
}

void Update()
{
    if(old_window_width == T_Window::width && old_window_height == T_Window::height){return;}

    offset_x = (T_Window::width  / 2) - (T_Window::MIN_WIDTH  / 2);
    offset_y = (T_Window::height / 2) - (T_Window::MIN_HEIGHT / 2);

    if(T_Window::width > T_Window::MIN_WIDTH * (scale + 1)){
    if(T_Window::height > T_Window::MIN_HEIGHT * (scale + 1)){
        scale++;
    }
    }


    old_window_width  = T_Window::width;
    old_window_height = T_Window::height;

    SDL_Rect viewport;
    viewport.x = offset_x;
    viewport.y = offset_y;
    viewport.w = T_Window::MIN_WIDTH  * scale;
    viewport.h = T_Window::MIN_HEIGHT * scale;

    SDL_RenderSetViewport(renderer, &viewport);

}

void Clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Present()
{
    SDL_RenderPresent(renderer);
}

void Destroy()
{
    if(renderer != nullptr){SDL_DestroyRenderer(renderer);}
}

void FillViewPort()
{
    target = {0, 0, T_Window::MIN_WIDTH * scale, T_Window::MIN_WIDTH * scale};

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &target);
}

void RenderAtTarget(int _x, int _y)
{
    target = {_x, _y, 32, 32};

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &target);
}

}