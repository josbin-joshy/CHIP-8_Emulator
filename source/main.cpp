#include"chip8.hpp"
#include<string>
Chip8 chip8
int main(int argc, char** argv)
{
    std::string filename{argv[argc-1]};
    chip8::loadROM(filename);
}