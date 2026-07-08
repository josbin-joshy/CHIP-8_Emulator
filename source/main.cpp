#include<iostream>
#include<filesystem>
#include<SDL2/SDL.h>
#include"chip8.hpp"


void updatekeypad(Chip8 &chip8)
{
    const uint8_t* key{SDL_GetKeyboardState(nullptr)};

    //1 2 3 C
    //4 5 6 D
    //7 8 9 E
    //A 0 B F

    chip8.keypad[0] = key[SDL_SCANCODE_X];  //0
    chip8.keypad[1] = key[SDL_SCANCODE_1];  //1
    chip8.keypad[2] = key[SDL_SCANCODE_2];  //2
    chip8.keypad[3] = key[SDL_SCANCODE_3];  //3

    chip8.keypad[4] = key[SDL_SCANCODE_Q];  //4
    chip8.keypad[5] = key[SDL_SCANCODE_W];  //5
    chip8.keypad[6] = key[SDL_SCANCODE_E];  //6
    chip8.keypad[7] = key[SDL_SCANCODE_A];  //7

    chip8.keypad[8] = key[SDL_SCANCODE_S];  //8
    chip8.keypad[9] = key[SDL_SCANCODE_D];  //9
    chip8.keypad[10] = key[SDL_SCANCODE_Z]; //A
    chip8.keypad[11] = key[SDL_SCANCODE_C]; //B

    chip8.keypad[12] = key[SDL_SCANCODE_4]; //C
    chip8.keypad[13] = key[SDL_SCANCODE_R]; //D
    chip8.keypad[14] = key[SDL_SCANCODE_F]; //E
    chip8.keypad[15] = key[SDL_SCANCODE_V]; //F
}


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


    uint32_t lastick{SDL_GetTicks()};

    while(runflag)
    {

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                runflag = false;
        
            if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                runflag = false;
            }        
        }


        updatekeypad(chip8);

        chip8.cycle();

        uint32_t current{SDL_GetTicks()};

        if(lastick - current >= 16)
        {
            if(chip8.delayTimer > 0)
                --chip8.delayTimer;
            if(chip8.soundTimer > 0)
                --chip8.soundTimer;
            
            lastick = current;
        }


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

        SDL_Delay(3); //333Hz

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}