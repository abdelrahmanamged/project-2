#include "VoleMachineClass.h"
#include <iostream>

using namespace std;

VoleMachine::VoleMachine() {
    // Components are initialized by their default constructors
}

void VoleMachine::start() {
    bool running = true;
    while (running) {
        ui.showMenu();
        int choice = ui.getChoice();

        switch (choice) {
        case 1: {
            string filename;
            cout << "Enter program filename (e.g., program.txt): ";
            cin >> filename;
            // internally asks user for the address via validaddress()
            loadProgram(filename, 0);
            break;
        }
        case 2:
            runProgram();
            break;
        case 3:
            stepProgram();
            break;
        case 4:
            ui.displayMachineState(cpu, memory, registers, screen);
            ui.waitForEnter();
            break;
        case 5:
            reset();
            cout << "Machine has been reset.\n";
            break;
        case 6:
            running = false;
            cout << "Shutting down simulator. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

bool VoleMachine::loadProgram(string fileName, int address) {
    try {
        programloader loader(fileName);
        loader.loadfromfile();
        loader.parseline();
        loader.validaddress();      // programlaoder code handles user input for address here
        loader.loadtomemory(memory);

        // Sync CPU's PC to the address the user just entered in loader
        cpu.setPC(loader.address);
        cout << "Program loaded successfully!\n";
        return true;
    }
    catch (const exception& e) {
        cout << "Failed to load program: " << e.what() << "\n";
        return false;
    }
}

void VoleMachine::runProgram() {
    if (cpu.isHalted()) {
        cout << "CPU is halted. Please reset and load a program to run.\n";
        return;
    }

    cout << "Executing program...\n";
    // Using teammate's CPU run method
    cpu.run(memory, registers);
    cout << "Execution finished or halted.\n";
}

void VoleMachine::stepProgram() {
    if (cpu.isHalted()) {
        cout << "CPU is halted. Cannot step further.\n";
        return;
    }

    cpu.step(memory, registers);
    cout << "Executed one step.\n";
    ui.displayMachineState(cpu, memory, registers, screen);
}

void VoleMachine::reset() {
    memory.clear();
    registers.clear();
    screen.clear();

    // The CPU doesn't have a reset function for the halted flag in the teammate's code,
    // so we re-instantiate it to get a fresh CPU with halted = false and PC = 0.
    cpu = CPU();
}