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
    outputBuffer += static_cast<char>(value);
}
void ScreenDisplay::display()const
{
    cout << outputBuffer;
}
void ScreenDisplay::clear()
{
    outputBuffer.clear();
}