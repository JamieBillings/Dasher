#ifndef __RENDERER__DASHER
#define __RENDERER__DASHER

namespace T_Renderer
{
    SDL_Renderer* renderer;

    int scale    = 1;
    int offset_x = 0;
    int offset_y = 0;

    int old_window_width  = 640;
    int old_window_height = 480;
    
    SDL_Rect target;
    SDL_Rect source;

    void Create();
    void Update();

    void Clear();
    void Present();

    void Destroy();

    //TESTING FUNCTIONS
    void FillViewPort(); //Testing the render scale and offset functionality

}

#endif