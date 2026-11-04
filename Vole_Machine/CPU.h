#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Memory.h"
#include"RegisterFile.h"
using namespace std;
class CPU
{
private:
    int pc;
    string ir;
    bool halted;

public:
CPU();
    string fetch(Memory &m) {};
    void excute() {}
    void step(Memory &m) {}
    void run(Memory &m) {}
    void set_pc(int address);
    void get_pc() {}
    string get_ir() {}
    bool get_helted() {}
};
