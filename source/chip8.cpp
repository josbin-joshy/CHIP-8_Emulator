#include<cstdint>
#include<fstream>
#include<cstring>
#include<chrono>
#include<random>
#include<iostream>
#include"chip8.hpp"


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





Chip8::Chip8() : randGen(std::chrono::system_clock::now().time_since_epoch().count())
{
    //initialise PC
    pc = START_ADDRESS;

    //loading font into memory
    for(unsigned int i = 0; i < FONTSET_SIZE; ++i)
    {
        memory[FONTSET_START_ADDRESS+i] = fontset[i];
    }   

    //initialize RNG
	randByte = std::uniform_int_distribution<uint8_t>(0, 255U);
    

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

void Chip8::OP_1nnn()
{
    uint16_t address = opcode & 0x0FFFu;
    pc = address;
}

void Chip8::OP_2nnn()
{
    uint16_t address = opcode & 0x0FFFu;
    stack[stkptr] = pc;
    ++stkptr;    
    pc = address;
}

void Chip8::OP_3xkk()
{
    uint16_t Vx = (opcode & 0x0F00u) >> 8u;
    uint16_t kk = opcode & 0x00FFu;

    //kk is a random value 
    //checks if the Vx register value is same as kk
    //if true icrement by 2
    if(registers[Vx] == kk)
        pc += 2;
}

void Chip8::OP_4xkk()
{
    uint16_t Vx = (opcode & 0x0F00u) >> 8u;
    uint16_t kk = opcode & 0x00FFu;

    //checks if the value at the Vx register is not equal to kk
    //if true incremetns pc by 2 :0
    if(registers[Vx] != kk)
        pc += 2;
}

void Chip8::OP_5xy0()
{
    uint16_t Vx = (opcode & 0x0F00u) >> 8u;
    uint16_t Vy = (opcode & 0x00F0u) >> 4u;

    //checking if the values of registers Vx and Vy are equal
    // if true then increment pc by 2 once again   :()
    if(registers[Vx] == registers[Vy])
        pc += 2;
}

void Chip8::OP_6xkk()
{
    uint16_t Vx = (opcode & 0x0F00u) >> 8u;
    uint16_t kk = opcode & 0x00FFu;
    registers[Vx] = kk;
}

void Chip8::OP_7xkk()
{
    uint16_t Vx = (opcode & 0x0F00u) >> 8u;
    uint16_t kk = opcode & 0x00FFu;
    registers[Vx] += kk;
}

void Chip8::OP_8xy0()
{
    uint16_t Vx = (opcode & 0x0F00u) >> 8u;
    uint16_t Vy = (opcode & 0x00F0u) >> 4u;
    registers[Vx] = registers[Vy];
}

void Chip8::OP_8xy1()
{
    uint16_t Vx = (opcode & 0x0F00u) >> 8u;
    uint16_t Vy = (opcode & 0x00F0u) >> 4u;
    registers[Vx] |= registers[Vy];
}

void Chip8::OP_8xy2()
{
    uint16_t Vx = (opcode & 0x0F00u) >> 8u;
    uint16_t Vy = (opcode & 0x00F0u) >> 4u;
    registers[Vx] &= registers[Vy];
}

void Chip8::OP_8xy3()
{
    uint16_t Vx = (opcode & 0x0F00u) >> 8u;
    uint16_t Vy = (opcode & 0x00F0u) >> 4u;
    registers[Vx] ^= registers[Vy];
}

void Chip8::OP_8xy4()
{
    uint16_t Vx = (opcode & 0x0F00u) >> 8u;
    uint16_t Vy = (opcode & 0x00F0u) >> 4u;
    uint16_t sum = registers[Vx] + registers[Vy];
    
    if(sum > 255U)
        registers[0x000F] = 1;
    else
        registers[0x000F] = 0;

    registers[Vx] = sum & 0x00FFu;
}

void Chip8::OP_8xy5()
{
    uint16_t Vx = (opcode & 0x0F00u) >> 8u;
    uint16_t Vy = (opcode & 0x00F0u) >> 4u;
    
    if(registers[Vx] > registers[Vy])
        registers[0x000F] = 1;
    else 
        registers[0x000F] = 0;
    
    registers[Vx] -= registers[Vy];
}

void Chip8::OP_8xy6()
{
    uint16_t Vx = (opcode & 0x0F00u) >> 8u;
    
    //if least significant digit is 1 then the flag is 1 else 0, thats all 
    //;)
    registers[0x000F] = (registers[Vx] & 0x0001u);

    //divide by 2
    registers[Vx] >>= 1;
}

void Chip8::OP_8xy7()
{
    uint16_t Vx = (opcode & 0x0F00u) >> 8u;
    uint16_t Vy = (opcode & 0x00F0u) >> 4u;
    if(registers[Vy] > registers[Vy])
        registers[0x000F] = 1;
    else    
        registers[0x000F] = 0;
    
    registers[Vx] = registers[Vy] - registers[Vx];
}

void Chip8::OP_8xyE()
{
    uint16_t Vx = (opcode & 0x0F00u) >> 8u;
    registers[0x000F] = (registers[Vx] & 0x0080u) >> 7u;
    registers[Vx] <<= 1;
}

void Chip8::OP_9xy0()
{
    uint16_t Vx = (opcode & 0x0F00u) >> 8u;
    uint16_t Vy = (opcode & 0x00F0u) >> 4u;
    if(registers[Vx] != registers[Vy])
        pc += 2;
}

void Chip8::OP_Annn()
{
    uint16_t address = opcode & 0x0FFFu;
    index = address;
}

void Chip8::OP_Bnnn()
{
    uint16_t address = opcode & 0x0FFFu;
    pc = registers[0] + address;
}

void Chip8::OP_Cxkk()
{
    uint16_t Vx = (opcode & 0x0F00u) >> 8u;
    uint16_t kk = opcode & 0x00FFu;

    registers[Vx] = randByte(randGen) & kk;
}


