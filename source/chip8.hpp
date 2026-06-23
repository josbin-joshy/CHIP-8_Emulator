#pragma once
#include<cstdint>

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
    void OP_8xy4();  //Vx = Vx + Vy
    void OP_8xy5();  //Vx = Vx - Vy
    void OP_8xy6();  //this one is confusing
    void OP_8xy7();
    void OP_8xyE();
    void OP_9xy0();

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