#pragma once
#include <iostream>
#include <string>
#include "Memory.h"
#include "RegisterFile.h"
using namespace std;
class CPU
{
private:
    int pc;
    string ir;
    bool halted;

    int Int(char c)
    {
        string digits = "0123456789ABCDEF";
        return digits.find(c);
    }
public:
    CPU()
    {
        pc = 0;
        ir = "";
        halted = false;
    }
    string fetch(Memory &m)
    {
        string digits = "0123456789ABCDEF";
        int s1 = m.read(pc);
        int s2 = m.read(pc + 1);
        ir = "";
        ir += digits[s1 / 16];
        ir += digits[s1 % 16];
        ir += digits[s2 / 16];
        ir += digits[s2 % 16];
        pc += 2;
        return ir;
    }
    void decode(int &op0, int &op1, int &op2, int &op3)
    {
        op0 = Int(ir[0]);
        op1 = Int(ir[1]);
        op2 = Int(ir[2]);
        op3 = Int(ir[3]);
    }
    void execute(int op0, int op1, int op2, int op3, Memory &m, RegisterFile &r)
    {
        int address = op2 * 16 + op3;
        if (op0 == 1)
        {
            r.set(op1, m.read(address));
        }
        else if (op0 == 2)
        {
            r.set(op1, address);
        }
        else if (op0 == 3)
        {
            if (address == 0xFF)
                cout << static_cast<char>(r.get(op1));
            else
                m.write(address, r.get(op1));
        }
        else if (op0 == 4)
        {
            r.set(op3, r.get(op2));
        }
        else if (op0 == 5)
        {
            r.set(op1, r.get(op2) + r.get(op3));
        }
        else if (op0 == 0xB)
        {
            if (r.get(op1) == r.get(0))
                pc = address;
        }
        else if (op0 == 0xC)
        {
            halted = true;
        }
        else
        {
            cout << "Unknown opcode" << endl;
            halted = true;
        }
    }
    void step(Memory &m, RegisterFile &r)
    {
        int op0, op1, op2, op3;
        fetch(m);
        decode(op0, op1, op2, op3);
        execute(op0, op1, op2, op3, m, r);
    }
    void run(Memory &m, RegisterFile &r)
    {
        while (halted == false)
        {
            step(m, r);
        }
    }
    void setPC(int address) { pc = address; }
    int getPC() { return pc; }
    string getIR() { return ir; }
    bool isHalted() { return halted; }
};