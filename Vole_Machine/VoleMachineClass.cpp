#include "VoleMachineClass.h"
#include <iostream>

using namespace std;

VoleMachineClass::VoleMachineClass() {
    // Components are initialized by their default constructors
}

void VoleMachineClass::start() { // this is the mainstream of the machine. the int main() function in Vole_Machine.cpp calls this function to actually start working. It's an inf. loop that keeps working until the user decides to quit.
    bool running = true;
    while (running) {
        ui.showMenu();
        int choice = ui.getChoice();

        switch (choice) {
        case 1: {
            string filename;
            cout << "Enter program filename (e.g., program.txt): ";
            cin >> filename;
            loadProgram(filename); // Removed the '0' to let Abdo's methods pick the address. It calls Abdo's funciton and lets it handle the loading process.
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

bool VoleMachineClass::loadProgram(string fileName) { // Removed 'int address' so as to let abdo's funciton handle input process of the address itself.
    try {
        programloader loader(fileName);
        loader.loadfromfile();
        loader.parseline();
        loader.validaddress();      // Programloader code handles user input for address here
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

void VoleMachineClass::runProgram() {
    if (cpu.isHalted()) {
        cout << "CPU is halted. Please reset and load a program to run.\n";
        return;
    }

    cout << "Executing program...\n";
    cpu.run(memory, registers);
    cout << "Execution finished or halted.\n";
}

void VoleMachineClass::stepProgram() {
    if (cpu.isHalted()) {
        cout << "CPU is halted. Cannot step further.\n";
        return;
    }

    cpu.step(memory, registers);
    cout << "Executed one step.\n";
    ui.displayMachineState(cpu, memory, registers, screen);
}

void VoleMachineClass::reset() {
    memory.clear();
    registers.clear();
    screen.clear();

    // The CPU doesn't have a reset function for the halted flag,
    // so we reset it to get a fresh CPU using its default constructor.
    cpu = CPU();
}