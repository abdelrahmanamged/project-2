#include"RegisterFile.h"
#include<iomanip> // for (setw, setfill)
#include<stdexcept> // for (out_of_range)
#include<iostream>
using namespace std;
RegisterFile ::RegisterFile()
{
    registers.resize(16,0);//allocate 16 register intialized to 0.
}
uint8_t RegisterFile::get(int index)const 
{
    if (index<0 || index>15)//validate if index is within valid range (0 to 15).
    {
        throw out_of_range("Invalid Register index");
    }
    return registers[index];//get register index and return value of this register.
    
}
void RegisterFile::set(int index , uint8_t  value)
{
     if (index < 0 || index > 15)//validate if index is within valid range (0 to 15).
    {
        throw out_of_range("Invalid Register index");
    }
    registers[index]=value;   //set a specefic value to a specific register index.
}
void RegisterFile::display()const
{
    for (size_t i = 0; i < registers.size(); i++)
    {
        cout<<"R" << uppercase << hex << i << ":" //hex:dispaly num as hex , uppercase letters.
            << setw(2) << setfill('0') //setw(2) & stfill('0'):two digit wide padded with '0' :on left.
            << static_cast<int> (registers[i]) ;// cast uint8_t to int for correct numeric display.
            cout << endl;
    }
      cout << dec << setfill(' ')<< nouppercase; //reset stream state back to decimal and default space fill
}
void RegisterFile::clear()
{
    for (size_t i = 0; i < registers.size(); i++)
    {
        registers[i]=0;
    } 
}