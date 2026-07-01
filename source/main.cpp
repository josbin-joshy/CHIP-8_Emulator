#include"chip8.hpp"
#include<string>

Chip8 chip8;

int main(int argc, char** argv)
{
    const char* filename{argv[argc-1]};
    chip8.loadROM(filename);

}