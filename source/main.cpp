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

    SDL_Window* window{SDL_CreateWindow("CHIP-8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 640, SDL_WINDOW_SHOWN)};
    SDL_Renderer* renderer{SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)};

    //tryna fool the computer into thinking the pixels are smaller than it seems muhahaha
    SDL_RenderSetLogicalSize(renderer,64,32);

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

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,255,255,255);

        for(int y = 0 ; y < 32 ; ++y)
        {
            for(int x = 0 ; x < 64 ;++x)
            {
                if(chip8.video[x+y*64])
                {
                    SDL_Rect rect{x,y,1,1};
                    SDL_RenderFillRect(renderer,&rect);
                }
            }
        }

        

        SDL_RenderPresent(renderer);

        SDL_Delay(16); //62.5Hz cycles  close enoguh to 60fps

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}