#pragma once
#include <string>
#include "Memory.h"
#include "RegisterFile.h"
#include "ScreenDisplay.h" 

using namespace std;

class CPU
{
private:
    int Int(char c);
    int PC;
    string IR;
    bool halted;

public:
    CPU();
    std::string fetch(Memory& m);
    void decode(int& op0, int& op1, int& op2, int& op3);

    void execute(int op0, int op1, int op2, int op3, Memory& m, RegisterFile& r, ScreenDisplay& s);
    void step(Memory& m, RegisterFile& r, ScreenDisplay& s);
    void run(Memory& m, RegisterFile& r, ScreenDisplay& s);

    void setPC(int address);
    int getPC() const;
    string getIR() const;
    bool isHalted() const;
};