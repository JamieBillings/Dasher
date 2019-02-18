#ifndef __TEXTURE__DASHER
#define __TEXTURE__DASHER

#include <ctype.h>

struct Texture
{
    SDL_Texture* texture;

    int width;
    int height;

    void LoadTexture(std::string _file);
    void FreeImage();
};

struct Animation
{
    int max_frame_count;
    int frame_count;
    int frame_width;

    double speed;
    double time;

    bool loop;

    void Create();
};

#endif