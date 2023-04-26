#ifndef HELP_HPP
#define HELP_HPP

#include <iostream>
#include <vector>
using namespace std;

struct Help
{
    static string LowercaseString(string Input);
    static string RevserseString(string Input);
    static string GetFileExtension(string &FileName);
    static void RemoveFileExtension(string &FileName);
    static string GetRealFileName(string Argv);
    static bool ContainsBreakLine(string Input);
};

#endif