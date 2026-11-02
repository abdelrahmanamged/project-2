#pragma once
#include<string>
#include<cstdint>
class ScreenDisplay
{
    private:
        std::string outputBuffer;//string buffer to accumulate output characters sent from CPU/memory.
    public:
        ScreenDisplay();//default constructor.
        void write(std::uint8_t value);//recieve an 8-bit value (hex char) ,convert it and appends it to outputbuffer.
        void display()const;//display acumulated outputbuffer on screen.
        void clear();//clears outputbuffer reset screen.
};