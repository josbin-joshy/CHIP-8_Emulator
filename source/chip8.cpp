#include<cstdint>
#include<fstream>
#include<cstring>
// #include<chrono>
// #include<random>


constexpr uint16_t START_ADDRESS{0x200};
constexpr unsigned int FONTSET_START_ADDRESS {0x50};
static constexpr unsigned int FONTSET_SIZE{80};


uint8_t fontset[FONTSET_SIZE] = 
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };


class Chip8
{
    public:

    void loadROM(const char* filename);
    void OP_00E0();
    void OP_00EE();
    void OP_1nnn();

    public:
    uint8_t registers[16]{};
    uint8_t memory[4096]{};

    uint16_t index{};
    uint16_t pc{};

    uint16_t stack[16]{};
    uint8_t stkptr{};

    uint8_t delayTimer{};
    uint8_t soundTimer{};

    uint8_t keypad[16]{};

    uint32_t video[64*32]{};

    uint16_t opcode{};

    

    Chip8();
    
};


Chip8::Chip8()
{
    //initialise PC
    pc = START_ADDRESS;

    //loading font into memory
    for(unsigned int i = 0; i < FONTSET_SIZE; ++i)
    {
        memory[FONTSET_START_ADDRESS+i] = fontset[i];
    }

    


}

void Chip8::loadROM(const char* filename)
{
    //open file as binary stream and move fp to the end
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if(file.is_open())
    {
        //basically read the no of bytes and created a array of that size
        std::streamsize size{file.tellg()};

        //checking for overflow
        if(size > 4096-START_ADDRESS) return;

        //creating the array of that size
        char* buffer{new char[size]};

        //reading the file onto the new array 
        //first setting fp to start so that it can read
        file.seekg(0, std::ios::beg);
        file.read(buffer, size);

        //closing it cause i odnt need it anymore :)---
        file.close();

        //now we load it muhahah
        for(long i = 0; i < size; ++i)
        {
            memory[START_ADDRESS+i] = buffer[i];
        }

        //freeeeeeeeeeeeeee we dont like memory leaks
        delete[] buffer;
    }
    
}

void Chip8::OP_00E0()
{
    memset(video,0,sizeof(video));
}


void Chip8::OP_00EE()
{
    pc = stack[--stkptr];
}

void Chip::OP_1nnn()
{
    uint16_t address = opcode & 0x0FFFu;
    pc = address;
}