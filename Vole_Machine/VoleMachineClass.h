#pragma once
#include "CPU.h"
#include "Memory.h"
#include "RegisterFile.h"
#include "programloader.h"
#include "InstructionDecoder.h"
#include "ScreenDisplay.h"
#include "ConsoleUI.h"
#include <string>

class VoleMachineClass {
    CPU cpu;
    Memory memory;
    RegisterFile registers;
    InstructionDecoder decoder;
    ScreenDisplay screen;
    ConsoleUI ui;

public:
    VoleMachineClass();
    void start();
    bool loadProgram(std::string fileName, int address);
    void runProgram();
    void stepProgram();
    void reset();
};