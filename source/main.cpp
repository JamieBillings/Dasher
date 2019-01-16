#include <SDL2\SDL.h>

#include <string>
#include <cstdio>

namespace Global
{

bool running = true;

}

#include "include\os.h"
#include "include\window.h"
#include "include\renderer.h"
#include "include\texture.h"

#include "os.cpp"
#include "window.cpp"
#include "renderer.cpp"
#include "texture.cpp"

int Startup()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){return 1;}
    T_Window::Create();
    OS::Setup(T_Window::window);
    return 0;
}

int main(int argc, char* argv[])
{
    if(Startup() != 0){return 1;} 

    

    while(Global::running){

    }


    return 0;
}