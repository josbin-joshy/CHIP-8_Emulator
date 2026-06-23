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
    void OP_3xkk();
    void OP_4xkk();
    void OP_5xy0();

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