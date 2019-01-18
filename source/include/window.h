#ifndef __WINDOW__DASHER
#define __WINDOW__DASHER

namespace T_Window
{

SDL_Window* window;

const int MIN_WIDTH  = 640;
const int MIN_HEIGHT = 480;

int width;
int height;

void Create();
void Update();
void Destroy();

}

#endif