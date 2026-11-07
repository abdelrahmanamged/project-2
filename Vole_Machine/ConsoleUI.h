#pragma once
#include "CPU.h"
#include "Memory.h"
#include "RegisterFile.h"
#include "ScreenDisplay.h"
#include <iostream>
#include <string>

class ConsoleUI {
public:
    void showMenu();
    int getChoice();
    int getLoadAddress();
    int chooseExecutionMode();
    void displayMachineState(const CPU& cpu, const Memory& memory, const RegisterFile& registers, const ScreenDisplay& screen);
    void waitForEnter();
    bool askToContinue();
};