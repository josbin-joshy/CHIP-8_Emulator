#include<cstdint>
#include<fstream>
#define START_ADDRESS 0x200

class Chip8
{
    public:
    void loadROM(const *char filename);

    public:
    uint8_t registers[16]{};
    uint8_t memory[4096]{};

    uint16_t index{};
    uint16_t pc{};

    uint16_t stack[16]{};
    uint8_t stkptr{};

    uint8_t delayTimer{};
    uint8_t stackTimer{};

    uint8_t keypad[16]{};

    uint32_t video[64*32]{};

    uint16_t opcode{};
}

void Chip8::loadROM(const *char filename)
{
    //open file as binary stream and move fp to the end
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if(file.is_open())
    {
        //basically read the no of bytes and created a array of that size
        std::streampos size{file.tellg()};
        char* buffer{new char[size]};

        //reading the file onto the new array 
        //first setting fp to start so that it can read
        file.seekg(0, std::ios::beg);
        file.read(buffer, size);

        //closing it cause i odnt need it anymore :)---
        file.close();

        //now we load it muhahah
        for(long i = 0; i<size; ++i)
        {
            memory[START_ADDRESS+i] = buffer[i];
        }

        //freeeeeeeeeeeeeee we dont like memory leaks
        delete[] buffer;
    }
}