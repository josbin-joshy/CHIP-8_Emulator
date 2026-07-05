#include<iostream>
#include<filesystem>
#include<fmt/format.h>
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
    if(!(std::filesystem::exists(filename)))
    {
        std::cerr << filename <<" file does not exists! \n";
        return 1;
    }


    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        std::cerr << "Error Initialise SDL2 :" << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("CHIP-8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    chip8.loadROM(filename);

    bool runflag{true};
    SDL_Event event;
    while(runflag)
    {

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                runflag = false;
        }


        chip8.cycle();

        SDL_Delay(2); //500Hz cycles
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}