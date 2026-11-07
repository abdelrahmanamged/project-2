#include "programloader.h"
#include <iostream>
#include <string>
#include <vector>
#include <cctype>    // for isspace, toupper
#include <algorithm> // for std::remove_if

using namespace std;

// Constructor
programloader::programloader(string filename) {
    this->filename = filename;
}

// Load file
void programloader::loadfromfile() {
    txtfile.open(filename, ios::in);

    while (!z) {
        if (!txtfile.is_open()) {
            cout << "I cannot find the file, please try again\n";
            txtfile.clear();
            string y;
            cin >> y;

            // Update the filename and try opening again
            filename = y;
            txtfile.open(filename, ios::in);
        }
        else {
            z = true;
        }
    }

    while (getline(txtfile, x)) {
        if (!x.empty()) {
            fileloader.push_back(x);
        }
    }
    txtfile.close();
}

// Clean the lines (remove spaces + convert to uppercase)
void programloader::parseline() {
    for (string& line : fileloader) {
        // Remove all spaces and make uppercase
        string cleaned;
        for (char c : line) {
            if (!isspace(static_cast<unsigned char>(c))) {
                cleaned += static_cast<char>(toupper(static_cast<unsigned char>(c)));
            }
        }
        line = cleaned;
    }

    // Remove completely empty lines after cleaning
    fileloader.erase(
        remove_if(fileloader.begin(), fileloader.end(),
            [](const string& s) { return s.empty(); }),
        fileloader.end());
}

// Get a valid starting address
void programloader::validaddress() {
    cout << "Please enter an address you want to start from.\n"
        << "Make sure it is an even number between 0 and 255:\n";

    while (true) {
        cin >> address;

        if (address >= 0 && address <= 255 && address % 2 == 0) {
            break;
        }
        cout << "You have entered an invalid address. Try again:\n";
    }
}

// Load instructions into memory
void programloader::loadtomemory(Memory& m) {
    int currentAddress = address;

    for (const string& instruction : fileloader) {
        if (instruction.length() < 4) {   // safety check
            cerr << "Warning: instruction too short: " << instruction << '\n';
            continue;
        }

        // First two hex digits
        string byte1 = instruction.substr(0, 2);
        uint8_t value1 = static_cast<uint8_t>(stoi(byte1, nullptr, 16));
        m.write(currentAddress, value1);

        // Next two hex digits
        string byte2 = instruction.substr(2, 2);
        uint8_t value2 = static_cast<uint8_t>(stoi(byte2, nullptr, 16));
        m.write(currentAddress + 1, value2);

        currentAddress += 2;
    }
}