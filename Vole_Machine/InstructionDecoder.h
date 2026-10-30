#pragma once
#include<string>
#include "instruction.h"
class InstructionDecoder {
public:
	InstructionDecoder();
	instruction decode(const string& hex_instruction) const;
	bool validate(const string& hex_instruction) const;
	bool is_hex(char c) const;

};

