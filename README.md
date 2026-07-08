# PROJECT
Building a CHIP-8 Emulator [C++]

## Build

### CMake (recommended)

```bash 
mkdir build
cd build
cmake ..
cmake --build .
```
## RUN
``` Linux / MacOS
./chip8 ../path/to/rom
```

# CHIP-8 Emulator

A lightweight CHIP-8 emulator written in modern C++. This project emulates the original CHIP-8 virtual machine, allowing classic CHIP-8 programs and games to run on modern systems.


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



## References

* [Cowgod's CHIP-8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)
* [CHIP-8 Wikipedia Documentation](https://en.wikipedia.org/wiki/CHIP-8)
* [Tobias V. Langhoff's CHIP-8 Guide](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/)
* https://austinmorlan.com/posts/chip8_emulator/

## Test Roms

* https://github.com/kripod/chip8-roms.git
* https://github.com/Timendus/chip8-test-suite.git

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
