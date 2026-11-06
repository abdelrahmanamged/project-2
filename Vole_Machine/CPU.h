#pragma once
#include <string>
#include "Memory.h"
#include "RegisterFile.h"
using namespace std;
class CPU
{
private:
    int pc;
    std::string ir;
    bool halted;
    int Int(char c);

public:
    CPU();
    std::string fetch(Memory &m);
    void decode(int &op0, int &op1, int &op2, int &op3);
    void execute(int op0, int op1, int op2, int op3, Memory &m, RegisterFile &r);
    void step(Memory &m, RegisterFile &r);
    void run(Memory &m, RegisterFile &r);
    void setPC(int address);
    int getPC() const;
    string getIR() const;
    bool isHalted() const;
};
