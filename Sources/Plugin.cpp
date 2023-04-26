#include <iostream>
#include <fstream>
#include "Includes/Plugin.hpp"
#include "Includes/Help.hpp"
using namespace std;
#define _3GX_HEADER 0x24584733
#define _PLG_HEADER 0xE92D5FFF

unsigned int Plugin::GetHeader(string &FileName)
{
    static const int Mult[4] = {0x1, 0x100, 0x10000, 0x1000000};
    ifstream File(FileName, ios::binary);
    int Header = 0;
    for (int i = 0; i < 4; i++)
        Header += (unsigned char)(File.get()) * Mult[i];
    File.close();
    
    return Header;
}

int Plugin::GetHeaderVersion(string &FileName)
{
    ifstream File(FileName, ios::binary);
    string Output = "";
    for (int i = 0; i < 8; i++) Output += File.get();
    File.close();
    return (Output[7] - 0x30);
}

unsigned char Plugin::GetVersion(string &FileName, int Version)
{
    ifstream File(FileName, ios::binary);
    File.seekg(9 + Version);
    unsigned char Output = File.get();
    File.close();
    return Output;
}

string Plugin::GetCompatibility(string &FileName)
{
    ifstream File(FileName, ios::binary);
    File.seekg(0x30);
    const string Compatibility[3] = {"Console", "Citra", "Any"};
    return Compatibility[File.get() / 0x10];
}

string Plugin::GetMemorySize(string &FileName)
{
    ifstream File(FileName, ios::binary);
    File.seekg(0x30);
    char Read = File.get() & 0xF;
    if (Read == 7) return "2MiB";
    if (Read == 3) return "5MiB";
    if (Read == 0xB) return "10MiB";
    return "ERROR";
}

void Plugin::GetStringInfo(string &FileName, vector<string> &Info)
{
    ifstream File(FileName, ios::binary);
    File.seekg(Plugin::GetHeaderVersion(FileName) == 2 ? 0x94 : 0x3C);
    string Word = "";
    bool Loop = true;
    int Read = 0;
    while (Loop)
    {
        char Char = File.get();
        if (Char != 0)
        {
            Word += Char;
            //cout << Word << endl;
        }
        else
        {
            Info.push_back(Word);
            Word = "";
            Read++;
            if (Read == 4) Loop = false;
        }
    }
    File.close();
}