#pragma once
#include<vector>
#include<cstdint> // for (uint8_t)
using namespace std;
class RegisterFile
{
    private:
       std:: vector<std:: uint8_t> registers;//storage for cpu registers (16 registers).
    public:
        RegisterFile();//default constructor
        std:: uint8_t get(int index)const;//return 8-bit value stored in register at given index.
        void set(int index , std:: uint8_t  value);//writes 8-bit value in to register at specific index. 
        void display()const;//display current register contents(R0 to RF) on screen.
        void clear(); // reset all register value back to 0.
};