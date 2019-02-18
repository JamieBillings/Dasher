#ifndef __SPRITE__DASHER
#define __SPRITE__DASHER

struct Sprite
{
    Texture* source_sheet;
    Animation animation;

    SDL_Rect src_pos;
    SDL_Rect dst_pos;

    void Render();  
};

#endif