#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include <iostream>
#include <vector>
using namespace std;

struct Plugin
{
    struct Version
    {
        static const int Revision = 0, Minor = 1, Major = 2;
    };

    static const unsigned int   _3GX_HEADER = 0x24584733,
                                _PLG_HEADER = 0xE92D5FFF;
    static unsigned int GetHeader(string &FileName);
    static int GetHeaderVersion(string &FileName);

    // Plginfo
    static unsigned char GetVersion(string &FileName, int Version);
    static string GetCompatibility(string &FileName);
    static string GetMemorySize(string &FileName);
    static void GetStringInfo(string &FileName, vector<string> &Info);
};

#endif