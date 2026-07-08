//i did random things to this i messed up
//i don't know what i am doing anymore
#include<cstdint>
#include<fstream>
#include<cstring>
#include<chrono>
#include<random>
#include<iostream>
#include<vector>
#include"chip8.hpp"


constexpr uint16_t START_ADDRESS{0x200};
constexpr uint16_t FONTSET_START_ADDRESS {0x50};
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
        if(size < 0 || size > 4096-START_ADDRESS) 
        {
            std::cerr << "Invalid ROM Size!\n";
            return;
        }

        //creating the array of that size
        std::vector<char> buffer(size); 

        //reading the file onto the new array 
        //first setting fp to start so that it can read
        file.seekg(0, std::ios::beg);
        file.read((buffer.data()), size);

        

        //closing it cause i odnt need it anymore :)---
        file.close();

        //now we load it muhahah
        for(long i = 0; i < size; ++i)
        {
            memory[START_ADDRESS + i] = buffer[i];
        }

    }

    if(!file)
    {
        std::cerr << "Error Reading ROM file!\n";
        return;
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
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t kk = opcode & 0x00FFu;

    //kk is a random value 
    //checks if the Vx register value is same as kk
    //if true icrement by 2
    if(registers[Vx] == kk)
        pc += 2;
}

void Chip8::OP_4xkk()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t kk = opcode & 0x00FFu;

    //checks if the value at the Vx register is not equal to kk
    //if true incremetns pc by 2 :0
    if(registers[Vx] != kk)
        pc += 2;
}

void Chip8::OP_5xy0()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    //checking if the values of registers Vx and Vy are equal
    // if true then increment pc by 2 once again   :()
    if(registers[Vx] == registers[Vy])
        pc += 2;
}

void Chip8::OP_6xkk()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t kk = opcode & 0x00FFu;
    registers[Vx] = kk;
}

void Chip8::OP_7xkk()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t kk = opcode & 0x00FFu;
    registers[Vx] += kk;
}

void Chip8::OP_8xy0()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    registers[Vx] = registers[Vy];
}

void Chip8::OP_8xy1()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    registers[Vx] |= registers[Vy];
}

void Chip8::OP_8xy2()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    registers[Vx] &= registers[Vy];
}

void Chip8::OP_8xy3()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    registers[Vx] ^= registers[Vy];
}

void Chip8::OP_8xy4()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    uint16_t sum = registers[Vx] + registers[Vy];
    
    if(sum > 255U)
        registers[0x000F] = 1;
    else
        registers[0x000F] = 0;

    registers[Vx] = sum & 0x00FFu;
}

void Chip8::OP_8xy5()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    
    if(registers[Vx] > registers[Vy])
        registers[0x000F] = 1;
    else 
        registers[0x000F] = 0;
    
    registers[Vx] -= registers[Vy];
}

void Chip8::OP_8xy6()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    
    //if least significant digit is 1 then the flag is 1 else 0, thats all 
    //;)
    registers[0x000F] = (registers[Vx] & 0x0001u);

    //divide by 2
    registers[Vx] >>= 1;
}

void Chip8::OP_8xy7()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    if(registers[Vy] > registers[Vx])
        registers[0x000F] = 1;
    else    
        registers[0x000F] = 0;
    
    registers[Vx] = registers[Vy] - registers[Vx];
}

void Chip8::OP_8xyE()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    registers[0x000F] = (registers[Vx] & 0x0080u) >> 7u;
    registers[Vx] <<= 1;
}

void Chip8::OP_9xy0()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
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
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t kk = opcode & 0x00FFu;

    registers[Vx] = randByte(randGen) & kk;
}

void Chip8::OP_Dxyn()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    uint8_t byte = opcode & 0x000Fu;

    //modulus is to wrap around the screen
    uint8_t xPos = registers[Vx] % VIDEO_WIDTH;
    uint8_t yPos = registers[Vy] % VIDEO_HEIGHT;

    registers[0x000F] = 0;

    for(unsigned int row = 0 ; row < byte ; ++row)
    {
        //reading it from memory
        uint8_t sprite = memory[index + row];
        
        for(unsigned int col = 0 ; col < 8 ; ++col)
        {
            uint8_t spritePixel = sprite & (0x0080u >> col);
            uint32_t* screenPixel = &video[(xPos + col) + (VIDEO_WIDTH * (yPos + row))];
            if(spritePixel)
            {
                if(*screenPixel == 0xFFFFFFFF)
                {
                    registers[0x000F] = 1;
                }

                *screenPixel ^= 0xFFFFFFFF;
            }
        }
    }

}

void Chip8::OP_Ex9E()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t key = registers[Vx];
    if(keypad[key])
        pc+=2;
}

void Chip8::OP_ExA1()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t key = registers[Vx];
    if(!keypad[key])
        pc+=2;
}

void Chip8::OP_Fx07()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    registers[Vx] = delayTimer;
}
void Chip8::OP_Fx0A()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    for(uint8_t i = 0 ; i < 16 ; ++i)
    {
        if(keypad[i])
        {
            registers[Vx] = i;
            return;
        }
    }
    pc-=2;
}

void Chip8::OP_Fx15()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    delayTimer = registers[Vx];
}

void Chip8::OP_Fx18()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    soundTimer = registers[Vx];
}

void Chip8::OP_Fx1E()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    index += registers[Vx];
}

void Chip8::OP_Fx29()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    index = FONTSET_START_ADDRESS + (5 * registers[Vx]);
}

void Chip8::OP_Fx33()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint16_t value = registers[Vx];

    //1
    memory[index+2] = value % 10;
    value /= 10;

    //10
    memory[index+1] = value % 10;
    value /= 10;

    //100
    memory[index] = value % 10;
}

void Chip8::OP_Fx55()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    for( uint8_t i = 0 ; i <= Vx ; ++i)
    {
        memory[index + i] = registers[i];
    }
}

void Chip8::OP_Fx65()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    for(uint8_t i = 0 ; i <= Vx ; ++i)
    {
        registers[i] = memory[index + i];
    }
}

//meow
void Chip8::cycle()
{
    //fetching instrucitons
    opcode = (memory[pc] << 8u) | memory[pc + 1];
    pc += 2;

    //
    switch((opcode & 0xF000u) >> 12u)
    {


        case 0:
            if(opcode & 0x000Fu)
                OP_00EE();
            else
                OP_00E0();
            break;
        
        case 1:
            OP_1nnn();
            break;
        case 2:
            OP_2nnn();
            break;

        case 3:
            OP_3xkk();
            break;
        

        case 4:
            OP_4xkk();
            break;

        case 5:
            OP_5xy0();
            break;
        
        case 6:
            OP_6xkk();
            break;
        case 7:
            OP_7xkk();
            break;
        

        case 8:
            switch(opcode & 0x000Fu)
            {
                case 0:
                    OP_8xy0();
                    break;
                
                case 1:
                    OP_8xy1();
                    break;
                
                case 2:
                    OP_8xy2();
                    break;
                
                case 3:
                    OP_8xy3();
                    break;

                case 4:
                    OP_8xy4();
                    break;
                
                case 5:
                    OP_8xy5();
                    break;

                case 6:
                    OP_8xy6();
                    break;

                case 7:
                    OP_8xy7();
                    break;
                
                case 0xEu:
                    OP_8xyE();
                    break;
            }
            break;
        
        case 9:
            OP_9xy0();
            break;
        
        case 0xAu:
            OP_Annn();
            break;

        case 0xBu:
            OP_Bnnn();
            break;

        case 0xCu:
            OP_Cxkk();
            break;
        
        case 0xDu:
            OP_Dxyn();
            break;
        
        case 0xEu:
            if((opcode & 0x000Fu) == 0x000Eu)
                OP_Ex9E();
            else
                OP_ExA1();
            break;
        
        case 0xFu:
            switch(opcode & 0x00FFu)
            {
                case 0x0007u:
                    OP_Fx07();
                    break;
                
                case 0x000Au:
                    OP_Fx0A();
                    break;

                case 0x0015u:
                    OP_Fx15();
                    break;

                case 0x0018u:
                    OP_Fx18();
                    break;

                case 0x001Eu:
                    OP_Fx1E();
                    break;
                
                case 0x0029u:
                    OP_Fx29();
                    break;
                
                case 0x0033u:
                    OP_Fx33();
                    break;
                
                case 0x0055u:
                    OP_Fx55();
                    break;
                
                case 0x0065u:
                    OP_Fx65();
                    break;
            }
            break;
    }

}
