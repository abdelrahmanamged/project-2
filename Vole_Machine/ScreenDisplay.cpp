#include"ScreenDisplay.h"
#include<iostream>
#include<iomanip>
#include<sstream>
using namespace std;
ScreenDisplay::ScreenDisplay()
{
}
void ScreenDisplay::write(uint8_t value)
{
    stringstream ss;
    ss << uppercase << hex << setw(2) << setfill('0') << static_cast<int>(value);
    outputBuffer += ss.str()+" ";//append formatted hex string with a newline to output buffer.
}
void ScreenDisplay::display()const
{
    cout << outputBuffer;
}
void ScreenDisplay::clear()
{
    outputBuffer.clear();
}