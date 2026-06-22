# CHIP-8_Emulator
Building a CHIP-8 Emulator [C++]


# CHIP-8 Emulator

A lightweight CHIP-8 emulator written in modern C++. This project emulates the original CHIP-8 virtual machine, allowing classic CHIP-8 programs and games to run on modern systems.

## Features

* Complete CHIP-8 CPU implementation
* 4 KB memory emulation
* 16 general-purpose 8-bit registers (V0–VF)
* Index register (I)
* Program counter and stack support
* 64×32 monochrome display
* Hexadecimal keypad input (16 keys)
* Delay and sound timers
* ROM loading support
* Cross-platform C++ codebase
* Configurable execution speed

## CHIP-8 Overview

CHIP-8 is an interpreted programming language originally developed by Joseph Weisbecker in the 1970s. It was designed to make game development easier on early microcomputers.

### System Specifications

| Component | Description               |
| --------- | ------------------------- |
| Memory    | 4096 bytes                |
| Registers | 16 × 8-bit                |
| Stack     | 16 levels                 |
| Display   | 64 × 32 pixels            |
| Input     | 16-key hexadecimal keypad |
| Timers    | Delay timer, Sound timer  |

## Project Structure

```text
chip8-emulator/
├── include/
│   ├── Chip8.hpp
│   ├── Display.hpp
│   ├── Keyboard.hpp
│   └── Opcodes.hpp
│
├── src/
│   ├── Chip8.cpp
│   ├── Display.cpp
│   ├── Keyboard.cpp
│   ├── Opcodes.cpp
│   └── main.cpp
│
├── roms/
│   ├── pong.ch8
│   ├── tetris.ch8
│   └── invaders.ch8
│
├── assets/
│   └── fonts.bin
│
├── CMakeLists.txt
└── README.md
```

## Requirements

* C++17 or newer
* CMake 3.16+
* SDL2 (recommended for graphics, input, and audio)

## Building

### Clone the Repository

```bash
git clone https://github.com/yourusername/chip8-emulator.git
cd chip8-emulator
```

### Configure

```bash
cmake -B build
```

### Build

```bash
cmake --build build --config Release
```

### Run

```bash
./build/chip8-emulator roms/pong.ch8
```

## Controls

| CHIP-8 | Keyboard |
| ------ | -------- |
| 1      | 1        |
| 2      | 2        |
| 3      | 3        |
| C      | 4        |
| 4      | Q        |
| 5      | W        |
| 6      | E        |
| D      | R        |
| 7      | A        |
| 8      | S        |
| 9      | D        |
| E      | F        |
| A      | Z        |
| 0      | X        |
| B      | C        |
| F      | V        |

## Emulator Architecture

### CPU Cycle

The emulator repeatedly performs:

1. Fetch opcode
2. Decode opcode
3. Execute instruction
4. Update timers
5. Refresh display
6. Process input

### Memory Layout

```text
0x000 - 0x1FF : Interpreter / Reserved
0x050 - 0x0A0 : Font sprites
0x200 - 0xFFF : Program ROM and work RAM
```

## Supported Instructions

The emulator supports all standard CHIP-8 instructions, including:

* Flow control
* Arithmetic operations
* Bitwise operations
* Sprite rendering
* Timers
* Keypad input
* Memory operations

Examples:

```text
00E0 - Clear screen
00EE - Return from subroutine
1NNN - Jump to address NNN
6XNN - Set VX = NN
7XNN - Add NN to VX
ANNN - Set I = NNN
DXYN - Draw sprite
```

## Testing

Test ROMs commonly used for validation:

* IBM Logo
* CHIP-8 Test Suite
* Corax+ Opcode Test
* BC_test
* Timendus CHIP-8 Test Suite

Run a ROM:

```bash
./chip8-emulator roms/test_opcode.ch8
```

## Future Improvements

* Super CHIP (SCHIP) support
* XO-CHIP support
* Save states
* Rewind functionality
* Debugger
* Breakpoints and memory inspection
* Disassembler
* Audio enhancements

## Performance

The emulator is designed to:

* Execute instructions efficiently
* Maintain accurate timer behavior
* Minimize input latency
* Remain portable across platforms

## References

* Cowgod's CHIP-8 Technical Reference
* CHIP-8 Wikipedia Documentation
* Tobias V. Langhoff's CHIP-8 Guide
* Timendus CHIP-8 Test Suite

## License

This project is licensed under the GNU General Public License v3.0 (GPL-3.0).

You are free to:

Use the software for any purpose
Study and modify the source code
Redistribute copies
Distribute modified versions

Under the terms of the GPL-3.0 license, any distributed modifications or derivative works must also be licensed under GPL-3.0 and include the corresponding source code.

For the full license text, see the LICENSE file in this repository or visit the GNU website:

https://www.gnu.org/licenses/gpl-3.0.en.html
