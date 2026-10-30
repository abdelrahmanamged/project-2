#include"instruction.h"
#include<iostream>
#include<string>
instruction::instruction()
{
	opcode = '0';
	operand1='0';
	 operand2='0';
	 operand3='0';
	 valid = false;;
}
instruction::instruction(char opc, char op1, char op2, char op3, bool is_valid)
	:opcode(opc),operand1(op1),operand2(op2),operand3(op3),valid(is_valid){ }
char instruction::get_opcode() const
{
	return opcode;
}
char instruction::get_operand1() const
{
	return operand1;
}
char instruction::get_operand2() const
{
	return operand2;
}
char instruction::get_operand3() const
{
	return operand3;
}
bool instruction::IS_valid() const
{
	return valid;
}
string instruction::tostring() const
{
	string s="";
	s += opcode;
	s += operand1;
	s += operand2;
	s += operand3;
	return s;
}