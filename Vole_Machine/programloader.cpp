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
