#include <iostream>
#include <fstream>
#include <vector>
#include "Includes/Help.hpp"
using namespace std;

string Help::LowercaseString(string Input)
{
    string Output = "";
    for (int i = 0; i < Input.length(); i++)
        Output += tolower(Input[i]);
    
    return Output;
}

string Help::RevserseString(string Input)
{
    string Output = "";
    for (int i = 0; i < Input.length(); i++)
        Output += Input[Input.length() - 1 - i];

    return Output;
}

string Help::GetFileExtension(string &FileName)
{
    string Extension = "";
    for (int i = 0; i < FileName.length(); i++)
    {
        unsigned char Char = FileName[FileName.length() - 1 - i];
        Extension += Char;
        if (Char == '.') break;
    }
    return Help::LowercaseString(Help::RevserseString(Extension));
}

void Help::RemoveFileExtension(string &FileName)
{
    string Extension = Help::GetFileExtension(FileName);
    string Output = "";
    for (int i = 0; i < FileName.length() - Extension.length(); i++)
        Output += FileName[i];

    FileName = Output;
}

string Help::GetRealFileName(string Argv)
{
    string Output = "", Reverse = Help::RevserseString(Argv);
    for (int i = 0; i < Reverse.length(); i++)
    {
        if (Reverse[i] == '\\') break;
        Output += Reverse[i];
    }
    return Help::RevserseString(Output);
}

bool Help::ContainsBreakLine(string Input)
{
    for (int i = 0; i < Input.length(); i++)
        if (Input[i] == '\n') return true;
    
    return false;
}