#include"loadrom.hpp"
#include"chip8.hpp"
void Rom::loadROM(const char* filename)
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