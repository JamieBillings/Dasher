#include <SDL2\SDL.h>

#include <string>
#include <cstdio>

#include "include\os.h"
#include "include\window.h"
#include "include\texture.h"

#include "os.cpp"
#include "window.cpp"
#include "texture.cpp"

int Startup()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){return 1;}
    return 0;
}

int main(int argc, char* argv[])
{
    if(Startup() != 0){return 1;}

    T_Window::Create();
    OS::Setup(T_Window::window);

    while(true){

    }


    return 0;
}