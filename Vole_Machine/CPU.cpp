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
    pc = 0;
    ir = "";
    halted = false;
}
string CPU::fetch(Memory &m)
{ // 40 34
    string digits = "0123456789ABCDEF";
    int s1 = m.read(pc);     // 40
    int s2 = m.read(pc + 1); // 34
    ir = "";
    ir += digits[s1 / 16]; // 2
    ir += digits[s1 % 16]; // 8
    ir += digits[s2 / 16]; // 2
    ir += digits[s2 % 16]; // 2
    pc += 2;
    return ir;
}
void CPU::decode(int &op0, int &op1, int &op2, int &op3)
{                     // ir=2822
    op0 = Int(ir[0]); // 2
    op1 = Int(ir[1]); // 8
    op2 = Int(ir[2]); // 2
    op3 = Int(ir[3]); // 2
}
void CPU::execute(int op0, int op1, int op2, int op3, Memory &m, RegisterFile &r)
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
        if (address == 0xFF)                       // 00FF=255
            cout << static_cast<char>(r.get(op1)); // Print the value stored at the address to the screen
        else
            m.write(address, r.get(op1)); // store the valu of op1 in address
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
            pc = address;
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
void CPU::step(Memory &m, RegisterFile &r)
{
    int op0, op1, op2, op3;
    fetch(m);
    decode(op0, op1, op2, op3);
    execute(op0, op1, op2, op3, m, r);
}
void CPU::run(Memory &m, RegisterFile &r)
{
    while (halted == false)
    {
        step(m, r);
    }
}
void CPU::setPC(int address) { pc = address; }
int CPU::getPC() const { return pc; }
string CPU::getIR() const { return ir; }
bool CPU::isHalted() const { return halted; }
