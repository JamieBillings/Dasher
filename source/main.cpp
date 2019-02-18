#include <SDL2\SDL.h>
#include <string>
#include <cstdio>

#define STB_IMAGE_IMPLEMENTATION
#include "include\stb_image.h"

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
#include "include\sprite.h"

#include "os.cpp"
#include "window.cpp"
#include "renderer.cpp"
#include "texture.cpp"
#include "timer.cpp"
#include "sprite.cpp"

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
    T_FPSTimer::GetTimeStep();
    T_Window::Update();
    T_Renderer::Update();
    
}

double _render_x_offset = 0;

int main(int argc, char* argv[])
{
    if(Startup() != 0){return 1;}
    
    Texture new_texture;
    new_texture.LoadTexture("spin.png");

    Sprite new_sprite;
    new_sprite.source_sheet = &new_texture;

    new_sprite.src_pos = {0,0,16,32};
    new_sprite.dst_pos = {100,100,100,100};


    while(Global::running){

        while(SDL_PollEvent(&Global::event)!= 0){
            if(Global::event.type == SDL_QUIT){Global::running = false;}
        }

        Update();

        T_Renderer::Clear();

        T_Renderer::FillViewPort();
        T_Renderer::RenderAtTarget(20,20);

        new_sprite.Render();

        T_Renderer::Present();

    }


    return 0;
}