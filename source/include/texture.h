#ifndef __TEXTURE__DASHER
#define __TEXTURE__DASHER

struct Texture
{
    SDL_Texture* texture;

    int width;
    int height;

    void LoadTextureFromImage(std::string _file);
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