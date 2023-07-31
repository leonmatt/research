/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include <string>

#include <iostream>

#include <chrono>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

#ifndef STANDARDCLIENT_H
#define STANDARDCLIENT_H

class StandardClient
{

public:

    StandardClient() {}
    ~StandardClient() {}

    void setupConnection(string, string);
    bool releaseConnection();

private:

    int socketNum;

    sockaddr_in serverAddr;

    int clientSocket;

    int getConnectionID();

    int receiveData();
    int sendMSG(string msg);

};

#endif // STANDARDCLIENT_H