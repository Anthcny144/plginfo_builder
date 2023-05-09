#include <iostream>
#include <fstream>
#include <vector>
#include "Includes/Help.hpp"
#include "Includes/Plugin.hpp"
using namespace std;

#define PROGRAM_NAME "plginfo_builder"
#define STOP(EC) Usage(); return EC;

void Usage()
{
    cout << "Usage: " << PROGRAM_NAME << " <input.3gx>" << endl;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        cout << "No input file!" << endl;
        STOP(-1);
    }
    string FileName = argv[1], RealFileName = Help::GetRealFileName(argv[1]); Help::RemoveFileExtension(RealFileName);
    if (Help::GetFileExtension(FileName) != ".3gx")
    {
        cout << "Invalid input file!" << endl;
        STOP(-2);
    }
    if (Plugin::GetHeader(FileName) != Plugin::_3GX_HEADER)
    {
        cout << "Invalid 3gx file!" << endl;
        STOP(-3);
    }
    if (Plugin::GetHeaderVersion(FileName) != 1 && Plugin::GetHeaderVersion(FileName) != 2)
    {
        cout << "Unknown 3gx header version, the program might not work correctly" << endl;
    }

    vector<string> Info;
    Plugin::GetStringInfo(FileName, Info);
    ofstream Output(RealFileName + ".plginfo", ios::binary);
    Output << "Author: " << Info[1] << endl;
    Output << "\nVersion: " << 
              "\n    Major: " << +Plugin::GetVersion(FileName, Plugin::Version::Major) <<
              "\n    Minor: " << +Plugin::GetVersion(FileName, Plugin::Version::Minor) <<
              "\n    Revision: " << +Plugin::GetVersion(FileName, Plugin::Version::Revision) << endl;
    Output << "\nTargets: 0" << endl;
    Output << "\nTitle: " << Info[0] << endl;
    Output << "\nSummary: " << Info[2] << endl;
    if (Help::ContainsBreakLine(Info[3])) Output << "Description: |\n" << Info[3] << endl;
    else Output << "\nDescription: " << Info[3];
    if (Plugin::GetHeaderVersion(FileName) == 2)
    {
        Output << "\nCompatibility: " << Plugin::GetCompatibility(FileName) << endl;
        Output << "\nMemorySize: " << Plugin::GetMemorySize(FileName);
    }
    Output.close();

    cout << (RealFileName + ".plginfo") << " created successfully!" << endl; 
    return 0;
}
