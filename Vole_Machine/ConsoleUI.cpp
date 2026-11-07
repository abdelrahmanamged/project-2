#include "ConsoleUI.h"

using namespace std;

void ConsoleUI::showMenu() {
    cout << "\n=== Vole Machine Simulator ===\n";
    cout << "1. Load Program from File\n";
    cout << "2. Run Program (Full Execution)\n";
    cout << "3. Step Program (Execute One Instruction)\n";
    cout << "4. Display Machine State (Registers, Memory, Screen)\n";
    cout << "5. Reset Machine\n";
    cout << "6. Exit\n";
    cout << "==============================\n";
}

int ConsoleUI::getChoice() {
    int choice;
    cout << "Enter your choice (1-6):\n";
    while (1) { // validation for choice. it must be an integer from 1 to 6 (inclusive)
        cin >> choice;
        if (choice <= 6 && choice >= 1) break;
        cout << "Please enter a valid choice. The choice you enter must be an integer from 1 to 6 (inclusive).\n";
    }
    return choice;
}
/*
int ConsoleUI::getLoadAddress() {
    int address;
    cout << "Enter starting memory address (Hex, e.g., 00 to FF, must be even): ";
    cin >> hex >> address >> dec; // cin expects decimal no. by default, but 'hex' here tells it to treat the next input as hexadecimal. the 'dec' at the end returns the default behavior of cin to let it expect decimals instead so it doesn't affect further inputs
    
    return address;
}
*/
int ConsoleUI::getLoadAddress() {
    int address;
    while (true) {
        cout << "Enter starting memory address (Hex, e.g., 00 to FF, must be even and not FF): ";
        cin >> hex >> address >> dec; // cin expects decimal no. by default, but 'hex' here tells it to treat the next input as hexadecimal. the 'dec' at the end returns the default behavior of cin to let it expect decimals instead so it doesn't affect further inputs

        // Check if the address is even and not FF (0xFF)
        if (address % 2 == 0 && address != 0xFF) {
            break; // Valid input, exit the loop
        }

        cout << "Invalid input. The address must be an even number and cannot be FF.\n";
    }

    return address;
}

int ConsoleUI::chooseExecutionMode() {
    int mode;
    cout << "1. Run full program\n";
    cout << "2. Step-by-step\n";
    cout << "Mode:\n";
    while (1) { // validation loop for choice as well. the choice must be either 1 or 2. the loop repeats until the user enters a valid (i.e., a value that is 1 or 2) choice.
        cin >> mode;
        if (mode == 1 || mode == 2) break;
        cout << "Please enter a valid mode. The only options are 1 or 2.\n";
    }
    return mode;
}

void ConsoleUI::displayMachineState(const CPU& cpu, const Memory& memory, const RegisterFile& registers, const ScreenDisplay& screen) { // THIS IS A READ-ONLY FUNCTION AND THUS WE USED A CONSTANT REFERENCE FOR THE PARAMETERS FOR OPTIMIZATION PURPOSES.
    cout << "\n--- CPU State ---\n";
    cout << "Program Counter (PC): " << uppercase << hex << cpu.getPC() << dec << "\n"; // hex here tells the program to print in hexadecimal temporarily so it prints 0A in hexadecimals instead of 10 in decimals
    cout << "Instruction Register (IR): " << cpu.getIR() << "\n";
    cout << "Halted: " << (cpu.isHalted() ? "Yes" : "No") << "\n"; // print "Yes" if the cpu.isHalted() returns true and print "No" if cpu.isHalted() returns false. this prints the halt state of the program.

    cout << "\n--- Registers ---\n";
    registers.display(); // calls yassine's function to display (print) the registers.

    cout << "\n--- Screen Output ---\n";
    screen.display();   // calls Yassine's function to display the screen.
    cout << "\n";

    cout << "\n--- Memory ---\n";
    memory.display();
}

void ConsoleUI::waitForEnter() { // pause the screen so the user can see the intermediate steps.
    cout << "Press Enter to continue...";
    cin.ignore(); // ignore the leftover \n from previous inputs.
    cin.get(); // pause the program until the user presses enter (i.e., enters '\n')
}

bool ConsoleUI::askToContinue() {
    char c;
    cout << "Execute next step? (Y/N): ";
    cin >> c;
    return (toupper(c) == 'Y');
}