#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>//that is a libarary to read or override or add on a file 
#include "Memory.h"

using namespace std;

class programloader
{
private:
    string filename;//the name of the file .txt

public:
    programloader(string filename) { this->filename = filename; }//constructor to make user get the file name that he want
    bool z = false;// I used it to know if the file open or not and I have made a while loop to make sure that the file is open  
    string x;// It is a string i used it to store the file instructions and to make sure it hasnot any empty lines 
    fstream txtfile;//I used it to read instructions from the file 
    vector<string> fileloader;//This is the vector I have used it to store all instructions from the file and make sure that doesnot have any spaces between it and , empty elments and ,make all elments in capitalize form  
    int address;//I used it to make the user chose the starting address that he want start from to store the instruction in memory and make sure it is even and in the range between 0 ,255

    void loadfromfile();//The function that I used to load the file.txt to read the instructions  
    void parseline();//The function that make the instruction that stored in the vector clean from any spaces or samll letters 
    void validaddress();//The function that i used to make suer to take a valid starting address  
    void loadtomemory(Memory& m);//I used it to store the instructions in the memory that i turned all elments in the vector to hex decimal and I shop the elemts to two that i can turn the number to hex as example (2005) i chop it to 20 and 05 using substr and turn it to hex decimal using stoi(who i want to turn,nullptr to ignore any empty or uninitialized elmint,16 because I want it to be hex decimal ) and used write function to store it in the memory 
};