#pragma once

#include <iostream>
#include <fstream>

using namespace std;
#define CONFIG_COUNT 3

class ConfigHandler {
    public:
        static int loadConfigValues();
        static int getConfigValue(string v_name); 
    private:
        int configs[CONFIG_COUNT];
        ConfigHandler(){}
};

int ConfigHandler::loadConfigValues()
{
    ifstream cFile("rtx.cfg");
    if (cFile.is_open())
    {
        string line;
        int i = 0;
        while(getline(cFile, line))
        {
            if (line.empty() || line[0] == "#")
            {
                continue;
            }

            auto delimiterPos = line.find("=");
            

            i++;
        }
    } else 
    {
        //TODO provide defaults
        cerr << "Could not find rtx.cfg to load settings.";
    }
    return 0;
}