#include"Memory.h"
#include<iostream>
#include<iomanip>// for output formating (hex, setw,setfill)
#include<stdexcept>//for exception (out_of_range)
using namespace std;
Memory::Memory()
{
     cells.resize(256,0); //allocate 256 memory cells intialized to 0.
}
uint8_t Memory::read(int address) const
{
        if (address < 0 || address > 255)//validate if address is within valid range (0 to 255).
        {
            throw out_of_range("Invalid memory address");
        }
        return cells[address]; //read address and return value of this memory address.
}
void Memory::write(int address,uint8_t value)
{
    if (address < 0 || address > 255)//validate if address is within valid range (0 to 255).
    {
        throw out_of_range("Invalid memory address");
    }
    cells[address]=value;   // write a specific value to a specific memory address .
}
void Memory::display() const 
{
    // displays the entire memory contents as a 16*16 grid in hex.
  for (int row = 0; row < 16; row++)
  {
   for (int column= 0; column < 16; column++)
   {
        int index = (row * 16) + column;
        cout << uppercase << hex //hex:dispaly num as hex , uppercase letters
            << setw(2) << setfill('0') << index //setw(2) & stfill('0'):two digit wide padded with '0' :on left,
            << ":"
            << setw(2) << static_cast<int>(cells[index]) // cast uint8_t to int for correct numeric display.
             << "  ";  
   } 
   cout << endl;
  }  
  cout << dec << setfill(' ') << nouppercase; //reset stream state back to decimal and default space fill
}
void Memory::clear()
{
    for (size_t i = 0; i < cells.size(); i++)
    {
        cells[i]=0;
    } 
}
