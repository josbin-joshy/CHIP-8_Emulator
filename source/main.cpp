#include<iostream>
#include<SDL2/SDL.h>
#include"chip8.hpp"


Chip8 chip8;

int main(int argc, char** argv)
{
    if(argc < 2) 
    {
        std::cerr << "usage: " << argv[0] << "<chip8ROM>\n";
        return 1;
    }

    const char* filename{argv[1]};

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL Error: " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("CHIP-8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64, 32, SDL_WINDOW_SHOWN);
    chip8.loadROM(filename);

    bool runflag{true};
    while(runflag)
    {
        chip8.cycle();
    }

    return 0;
}