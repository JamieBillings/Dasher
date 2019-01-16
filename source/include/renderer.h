#ifndef __RENDERER__DASHER
#define __RENDERER__DASHER

namespace T_Renderer
{
    SDL_Renderer* renderer;

    int render_scale;
    int render_offset_x;
    int render_offset_y;
    
    SDL_Rect render_target;
    SDL_Rect render_source;

    void Create();

    void RenderClear();
    void RenderPresent();

    void Destroy();

}

#endif