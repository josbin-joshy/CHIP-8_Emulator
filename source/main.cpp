#include"chip8.hpp"
#include<iostream>

Chip8 chip8;

int main(int argc, char** argv)
{
    if(argc < 2) 
    {
        std::cerr << "usage: " << argv[0] << "<chip8ROM>\n";
        return 1;
    }

    const char* filename{argv[argc-1]};
    chip8.loadROM(filename);

    bool runflag{true};
    while(runflag)
    {

    }

    return 0;
}