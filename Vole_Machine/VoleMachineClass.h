#pragma once
#include "CPU.h"
#include "Memory.h"
#include "RegisterFile.h"
#include "programloader.h"
#include "ScreenDisplay.h"
#include "ConsoleUI.h"
#include <string>

class VoleMachineClass {
    CPU cpu;
    Memory memory;
    RegisterFile registers;
    ScreenDisplay screen;
    ConsoleUI ui;

public:
    VoleMachineClass();
    void start(); // main operation stream. it's also called in int main() function in the main file which is Vole_Machine.cpp. It's an infinite while loop that keeps running until the user decides to quit.
    bool loadProgram(std::string fileName); // Removed unused 'int address'
    void runProgram();
    void stepProgram();
    void reset();
};