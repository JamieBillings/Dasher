namespace T_Window
{

void Create()
{
    window = SDL_CreateWindow("Dasher", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480, SDL_WINDOW_RESIZABLE);

    if(window == nullptr){OS::CreateErrorWindow("Couldn't Create Window", error_level::error);}
}

void Update()
{
    SDL_GetWindowSize(window, &width, &height);

    if(width < MIN_WIDTH){
        width = MIN_WIDTH;
        SDL_SetWindowSize(window, width, height);
    }

    if(height < MIN_HEIGHT){
        height = MIN_HEIGHT;
        SDL_SetWindowSize(window, width, height);
    }
}

void Destroy()
{
    if(window != nullptr){SDL_DestroyWindow(window);}

}

}
