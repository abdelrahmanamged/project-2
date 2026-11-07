#include <iostream>
#include "CPU.h"

using namespace std;

int CPU::Int(char c)
{
    string digits = "0123456789ABCDEF"; // A=10
    return digits.find(c);
}

CPU::CPU()
{
    PC = 0;
    IR = "";
    halted = false;
}

string CPU::fetch(Memory& m)
{ // 40 34
    string digits = "0123456789ABCDEF";
    int s1 = m.read(PC);     // 40
    int s2 = m.read(PC + 1); // 34
    IR = "";
    IR += digits[s1 / 16]; // 2
    IR += digits[s1 % 16]; // 8
    IR += digits[s2 / 16]; // 2
    IR += digits[s2 % 16]; // 2
    PC += 2;
    return IR;
}

void CPU::decode(int& op0, int& op1, int& op2, int& op3)
{                     // ir=2822
    op0 = Int(IR[0]); // 2
    op1 = Int(IR[1]); // 8
    op2 = Int(IR[2]); // 2
    op3 = Int(IR[3]); // 2
}

void CPU::execute(int op0, int op1, int op2, int op3, Memory& m, RegisterFile& r, ScreenDisplay& s)
{                                 // 2822
    int address = op2 * 16 + op3; // 34

    if (op0 == 1)                 // load the value inside the address in op1
    {
        r.set(op1, m.read(address));
    }
    else if (op0 == 2) // load the address in op1
    {
        r.set(op1, address);
    }
    else if (op0 == 3) // store
    {
        m.write(address, r.get(op1)); // store the value of op1 in address

        if (address == 0xFF)          // 00FF=255
        {
            s.write(r.get(op1));      // Send the value to the screen buffer
        }
    }
    else if (op0 == 4) // here i ignore op1 i make the op2 as a register and op3 also r1 =0
    {
        r.set(op3, r.get(op2)); // op1=0
    }
    else if (op0 == 5) // add Integer
    {
        r.set(op1, r.get(op2) + r.get(op3));
    }
    else if (op0 == 6) // add floating
    {
        r.set(op1, (r.get(op2) + r.get(op3)) & 0xFF);
    }
    else if (op0 == 7) // OR
    {
        r.set(op1, r.get(op2) | r.get(op3));
    }
    else if (op0 == 8) // AND
    {
        r.set(op1, r.get(op2) & r.get(op3));
    }
    else if (op0 == 9) // XOR
    {
        r.set(op1, r.get(op2) ^ r.get(op3));
    }
    else if (op0 == 0xA)//rotate
    {
        uint8_t val = r.get(op1);//00000110
        int rot = op3 % 8;//000000110
        uint8_t rotated = (val >> rot) | (val << (8 - rot));//00000001+10000000=10000001
        r.set(op1, rotated & 0xFF);
    }
    else if (op0 == 0xB) // op0=B jump
    {
        if (r.get(op1) == r.get(0)) // if op1 = R(0) jump to address
            PC = address;
    }
    else if (op0 == 0xC) // c000
    {
        halted = true;
    }
    else
    {
        cout << "Unknown opcode" << endl;
        halted = true;
    }
}

void CPU::step(Memory& m, RegisterFile& r, ScreenDisplay& s)
{
    int op0, op1, op2, op3;
    fetch(m);
    decode(op0, op1, op2, op3);
    execute(op0, op1, op2, op3, m, r, s);
}

void CPU::run(Memory& m, RegisterFile& r, ScreenDisplay& s)
{
    while (halted == false)
    {
        step(m, r, s);
    }
}

void CPU::setPC(int address) { PC = address; }
int CPU::getPC() const { return PC; }
string CPU::getIR() const { return IR; }
bool CPU::isHalted() const { return halted; }