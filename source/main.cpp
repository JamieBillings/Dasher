#include <SDL2\SDL.h>

#include <string>
#include <cstdio>

namespace Global
{

bool running = true;

SDL_Event event;

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
    T_Renderer::Create();
    return 0;
}

void Update()
{
    T_Window::Update();
    T_Renderer::Update();
}

int main(int argc, char* argv[])
{
    if(Startup() != 0){return 1;} 

    

    while(Global::running){
        while(SDL_PollEvent(&Global::event)!= 0){
            if(Global::event.type == SDL_QUIT){Global::running = false;}
        }

        Update();

        T_Renderer::Clear();

        T_Renderer::FillViewPort();
        T_Renderer::RenderAtTarget(20,20);

        T_Renderer::Present();


    }


    return 0;
}