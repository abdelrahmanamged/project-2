/*
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "programloader.h"
using namespace std;
class programloader
{
private:
    string filename;

public:
    programloader(string filename) { this->filename = filename; }

    bool z = false;
    string x;
    fstream txtfile;
    vector<string> fileloader;
    void loadfromfile()
    {
        txtfile.open(filename, ios::in);
        while (z != true)
        {
            if (!txtfile.is_open())
            {
                cout << "I canot find the file please try again " << "\n";
                txtfile.clear();
                string y;
                cin >> y;

                txtfile.open(y, ios::in);
            }
            else if (txtfile.is_open())
            {
                z = true;
            }
        }
        while (getline(txtfile, x))
        {
            if (x.empty() == 1)
            {
                continue;
            }
            else
            {
                fileloader.push_back(x);
            }
        }
        txtfile.close();
    }
    void parseline()
    {
        vector<string> parsel;
        string ex;
        for (int i = 0; i < fileloader.size(); i++)
        {
            ex = fileloader[i];
            for (int j = 0; j < ex.size();)
            {
                if (isspace(ex[j]))
                {
                    ex.erase(j, 1);
                }
                else
                {
                    j++;
                }
            }
            fileloader[i] = ex;
        }
        for (int i = 0; i < fileloader.size(); i++)
        {
            ex = fileloader[i];
            parsel.push_back(fileloader[i]);
            for (int j = 0; j < ex.size(); j++)
            {
                if (ex == "")
                {
                    parsel.pop_back();
                }
                else
                {
                    ex[j] = toupper(ex[j]);
                }
            }
            fileloader[i] = ex;
            parsel[i] = ex;
        }
        while (fileloader.size() > parsel.size())
        {
            fileloader.pop_back();
        }

        for (int i = 0; i < parsel.size(); i++)
        {
            fileloader[i] = parsel[i];
        }
    }
    int address;
    void validaddress()
    {
        bool valid = false;
        cout << "Please enter an address you want to start from. Make sure it is an even number between 0 and 255:\n";
        cin >> address;
        while (valid == false)
        {
            if (address <= 255 && address >= 0 && address % 2 == 0)
            {
                valid = true;
            }
            else
            {
                cout << "you have entered unvalid address \n";
                cin >> address;
            }
        }
    }
    void loadtomemory(Memory &m)
    {
        int currentaddress = address;

        string instruction;
        for (int i = 0; i < fileloader.size(); i++)
        {
            instruction = fileloader[i];
            string substr1 = instruction.substr(0, 2);
            uint8_t substr2 = stoi(substr1, nullptr, 16);
            m.write(currentaddress, substr2);

            substr1 = instruction.substr(2, 2);
            substr2 = stoi(substr1, nullptr, 16);
            m.write(currentaddress + 1, substr2);

            currentaddress += 2;
        }
    }
};


int main()
{
    Memory m;
    string filename;
    cout << "please Enter file name \n";
    cin >> filename;
    programloader p1(filename);
    p1.loadfromfile();
    p1.parseline();
    p1.validaddress();
    p1.loadtomemory(m);
}
*/

#include "programloader.h"
#include <cctype>          // for isspace, toupper

// Constructor
programloader::programloader(std::string filename)
{
    this->filename = filename;
}

// Load file
void programloader::loadfromfile()
{
    txtfile.open(filename, std::ios::in);

    while (!z)
    {
        if (!txtfile.is_open())
        {
            std::cout << "I cannot find the file, please try again\n";
            txtfile.clear();
            std::string y;
            std::cin >> y;
            txtfile.open(y, std::ios::in);
        }
        else
        {
            z = true;
        }
    }

    while (std::getline(txtfile, x))
    {
        if (!x.empty())
        {
            fileloader.push_back(x);
        }
    }
    txtfile.close();
}

// Clean the lines (remove spaces + convert to uppercase)
void programloader::parseline()
{
    for (std::string& line : fileloader)
    {
        // Remove all spaces
        std::string cleaned;
        for (char c : line)
        {
            if (!std::isspace(static_cast<unsigned char>(c)))
            {
                cleaned += static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
            }
        }
        line = cleaned;
    }

    // Optional: remove completely empty lines after cleaning
    fileloader.erase(
        std::remove_if(fileloader.begin(), fileloader.end(),
            [](const std::string& s) { return s.empty(); }),
        fileloader.end());
}

// Get a valid starting address
void programloader::validaddress()
{
    std::cout << "Please enter an address you want to start from.\n"
        << "Make sure it is an even number between 0 and 255:\n";

    while (true)
    {
        std::cin >> address;

        if (address >= 0 && address <= 255 && address % 2 == 0)
        {
            break;
        }
        std::cout << "You have entered an invalid address. Try again:\n";
    }
}

// Load instructions into memory
void programloader::loadtomemory(Memory& m)
{
    int currentAddress = address;

    for (const std::string& instruction : fileloader)
    {
        if (instruction.length() < 4)   // safety check
        {
            std::cerr << "Warning: instruction too short: " << instruction << '\n';
            continue;
        }

        // First two hex digits
        std::string byte1 = instruction.substr(0, 2);
        uint8_t value1 = static_cast<uint8_t>(std::stoi(byte1, nullptr, 16));
        m.write(currentAddress, value1);

        // Next two hex digits
        std::string byte2 = instruction.substr(2, 2);
        uint8_t value2 = static_cast<uint8_t>(std::stoi(byte2, nullptr, 16));
        m.write(currentAddress + 1, value2);

        currentAddress += 2;
    }
}