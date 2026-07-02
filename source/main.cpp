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
    chip8.loadROM(filename);

    bool runflag{true};
    while(runflag)
    {
        chip8.cycle();
    }

    return 0;
}