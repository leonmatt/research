/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include "RDMAConnection.h"

using namespace std;

void parseConfiguration(const string& configName, string (&vars)[4]);

int main(int argc, char *argv[], char *env[])
{

    string fname = "config.txt";
    string vars[4];

    parseConfiguration(fname, vars);

    // Allocate the infiniband connection
    cout << "Setting up connection for device: " << vars[0] << endl;
    RDMAConnection rdmaClient(vars[0]);

    // Set up the infiniband connection
    rdmaClient.setupConnection(vars[2], vars[3]);

    string msg = "Hello World!";

    string& msgRef = msg;

    rdmaClient.sendMSG(msgRef);

    return 0;

}

void parseConfiguration(const string& configName, string (&vars)[4])
{
    ifstream configFile;
    string delim = "=";
    string line, key, value;
    configFile.open(configName);
    if (configFile.is_open()) {
    
        while (getline(configFile, line)) {
            if (line.compare("") == 0)
                continue;
            size_t pos = line.find(delim);
            key   = line.substr(0, pos);
            value = line.substr(pos+1);
            key.erase(remove_if(key.begin(), key.end(), ::isspace), key.end());
            value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());
            if(key.compare("client_dev_name") == 0)
                vars[0] = value;
            if(key.compare("server_dev_name") == 0)
                vars[1] = value;
            if(key.compare("server_ip") == 0)
                vars[2] = value;
            if(key.compare("server_port") == 0)
                vars[3] = value;

        }

    }
}
