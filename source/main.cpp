#include <SDL2\SDL.h>

#include <cstring>
#include <cstdio>

#include "include\os.h"
#include "include\window.h"
#include "include\texture.h"

#include "os.cpp"
#include "window.cpp"
#include "texture.cpp"

int Startup()
{
    return 0;
}

int main(int argc, char* argv[])
{
    if(Startup() != 0){return 1;}
    return 0;
}