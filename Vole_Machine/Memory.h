#pragma once
#include<vector>
#include<cstdint>//for(uint8_t) provide data types size is determined by bit
class Memory
{
    private:
       std:: vector<uint8_t> cells; //memory storage:vector of 8_bit unsigned integers (1 byte per cell , range : 0 to 255).
    public:
        Memory();//default constructor
        std:: uint8_t read(int address)const; //read and return the 8_bit value that stored in the given memory address.
        void write(int address,std:: uint8_t value);//writes an 8_bit value to a specific memory address.
        void display()const;//display the current memory contents (address . value) on screen.
        void clear();//reset all memory cells back to 0.

};