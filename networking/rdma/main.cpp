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

void parseConfiguration(const string& configName, string (&names)[2]);

int main(int argc, char *argv[], char *env[])
{

    RDMAConnection client;
    RDMAConnection server;

    string fname = "config.txt";
    string connectionNames[2];

    parseConfiguration(fname, connectionNames);

    // Set up the infiniband connections
    client.setupConnection(connectionNames[0]);
    server.setupConnection(connectionNames[1]);

    // Release the infiniband connections
    client.releaseConnection();
    server.releaseConnection();

    return 0;

}

void parseConfiguration(const string& configName, string (&names)[2])
{
    ifstream configFile;
    string delim = "=";
    string line, key, value;
    configFile.open(configName);
    if (configFile.is_open()) {
    
        while (getline(configFile, line)) {
            size_t pos = line.find(delim);
            key   = line.substr(0, pos);
            value = line.substr(pos+1);
            key.erase(remove_if(key.begin(), key.end(), ::isspace), key.end());
            value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());
            if(key.compare("client_dev_name") == 0)
                names[0] = value;
            if(key.compare("server_dev_name") == 0)
                names[1] = value;

        }

    }
}
