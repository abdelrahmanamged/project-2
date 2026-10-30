#pragma once
#include<iostream>
#include<string>
using namespace std;
class instruction
{
private:
	char opcode;
	char operand1;
	char operand2;
	char operand3;
	bool valid;
public:
	

	instruction();
	instruction(char opc, char op1, char op2, char op3, bool is_valid = true);

	char get_opcode() const;
	char get_operand1() const;
	char get_operand2() const;
	char get_operand3() const;
	bool IS_valid() const;
	string tostring() const;
};

