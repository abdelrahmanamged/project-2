#include<string>
#include "instruction.h"
#include "InstructionDecoder.h"
#include <cctype>

using namespace std;
InstructionDecoder::InstructionDecoder(){}
//check if character is Hex or not 1e4f
bool InstructionDecoder::is_hex(char c) const
{
	
	c = toupper(static_cast<unsigned char>(c)); // safely convert c to unsigned char before passing it to toupper.
// this avoids undefined behavior if char has a negative value.
	//hexadicimal:0 1 2 3 4 5 6 7 8 9 A B C D E F
	return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'); //return true if hex 
															//return false if not hex	

}
// check safety of instruction and length
bool InstructionDecoder::validate(const string & hex_instruction) const
{
	if (hex_instruction.length() != 4) return false; //validate if length of instruction is 4 or not
	for (int i = 0; i < 4; i++)// check from instruction completely character by character if it is hix or not
	{
		if(!is_hex(hex_instruction[i])) 
			return false ;
	}
	char op = toupper(static_cast<unsigned char>(hex_instruction[0]));//op-code belong to[1 to c] according to instruction table

	if ((op >= '1' && op <= '9') || (op >= 'A' && op <= 'C'))
	{
		return true;		//check if op-code valid or not according to instruction table
	}
	return false;

}	
// dcode (تفكيك) the instruction and return an instruction object.
instruction InstructionDecoder::decode(const string& hex_instruction) const
{
	if (!validate(hex_instruction))
	{
		return instruction('0', '0', '0', '0', false); //rather than declare new object then intialize and return it
		//construct temprory object in ram then return it 
	}
	//after we check the instruction we will split them
	char op= toupper(static_cast<unsigned char>(hex_instruction[0])); 
	char op1= toupper(static_cast<unsigned char>(hex_instruction[1]));
	char op2= toupper(static_cast<unsigned char>(hex_instruction[2]));
	char op3= toupper(static_cast<unsigned char>(hex_instruction[3]));
	//return instruction wo(op, op1, op2, op3,true);
	return instruction(op, op1, op2, op3,true);
}


