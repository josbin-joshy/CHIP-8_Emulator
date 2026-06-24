#pragma once
#include<cstdint>
#include<random>

constexpr unsigned int KEY_COUNT{16};
constexpr unsigned int MEMORY_SIZE{4096};
constexpr unsigned int REGISTER_COUNT{16};
constexpr unsigned int STACK_COUNT{16};
constexpr unsigned int VIDEO_HEIGHT{32};
constexpr unsigned int VIDEO_WIDTH{64};

class Chip8
{
public:

    void loadROM(const char* filename);

    void OP_00E0();  //Clear Display CLS

    void OP_00EE();  //Return from Subroutine RET

    void OP_1nnn();  //jump to location nnn JP

    void OP_2nnn();  //call subroutine at nnn CALL 

    void OP_3xkk();  //checks if value of Vx == kk  and skips if true

    void OP_4xkk();  //checks if value of Vx != kk and skips if true

    void OP_5xy0();  //checks if values of Vx == Vy and skips if true


    void OP_6xkk();  //interpreter puts the value kk into Vx register

    void OP_7xkk();  //Vx = Vx + kk

    void OP_8xy0();  //Vx = Vy

    void OP_8xy1();  //Vx = Vx | Vy 

    void OP_8xy2();  //Vx = Vx & Vy

    void OP_8xy3();  //Vx = Vx ^ Vy

    void OP_8xy4();  //Vx = Vx + Vy, if sum greater than 255 flag is 1 else 0
                     // then lowest 8bits of the sum is kept in Vx

    void OP_8xy5();  //if Vx > Vy then flag is 1 else 0, Vx = Vx - Vy

    void OP_8xy6();  //this ones a bit confusing we check if the least significant bit of Vx is 1,
                     //if true flag is 1 else 0, then divide Vx by 2

    void OP_8xy7();  //almost same as 8xy5 but reverse

    void OP_8xyE();  //flag is 1 if most significant digit is 1 else 0,
                     //then Vx is multiplied by 2

    void OP_9xy0();  //if values of Vx != Vy then pc+=2

    void OP_Annn();  //value of register index is set to nnn (index to nnn)

    void OP_Bnnn();  //value of pc is set to nnn + V0

    void OP_Cxkk();  //generate a random number and & it with kk then store it in Vx(basically a ranodm numeber generaotr)

    void OP_Dxyn();  //DRW Vx, Vy, nibble

    void OP_Ex9E();  //SKP Vx

    void OP_ExA1();  //SKNP Vx

    void OP_Fx07();  //LD Vx, DT
    
    void OP_Fx0A();  //LD Vx, K

    void OP_Fx15();  //LD DT, Vx

    void OP_Fx18();  //LD ST, Vx
    
    void OP_Fx1E();  //ADD I, Vx
    
    void OP_Fx29();  //LD F, Vx
    
    void OP_Fx33();  //LD B, Vx
    
    void OP_Fx55();  //LD [I], Vx
    
    void OP_Fx65();  //LD Vx, [I]
    

public:
    uint8_t registers[REGISTER_COUNT]{};
    uint8_t memory[MEMORY_SIZE]{};

    uint16_t index{};
    uint16_t pc{};

    uint16_t stack[STACK_COUNT]{};
    uint8_t stkptr{};

    uint8_t delayTimer{};
    uint8_t soundTimer{};

    uint8_t keypad[16]{};

    uint32_t video[64*32]{};

    uint16_t opcode{};

    

    Chip8();


    //hmmmm
public:
    std::default_random_engine randGen;
	std::uniform_int_distribution<uint8_t> randByte;
    
};