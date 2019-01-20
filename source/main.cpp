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
#include "include\timer.h"

#include "os.cpp"
#include "window.cpp"
#include "renderer.cpp"
#include "texture.cpp"
#include "timer.cpp"

int Startup()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){return 1;}
    T_Window::Create();
    OS::Setup(T_Window::window);
    T_Renderer::Create();
    T_FPSTimer::Start();
    return 0;
}

void Update()
{
    T_FPSTimer::GetTimeStep();

    T_Window::Update();
    T_Renderer::Update();

    printf("timestep : %f \n", T_FPSTimer::time_step);
    printf("Preformance : %lld \n", SDL_GetPerformanceCounter());
    
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