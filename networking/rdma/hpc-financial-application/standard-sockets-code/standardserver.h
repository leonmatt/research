/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include <iostream>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#ifndef STANDARDSERVER_H
#define STANDARDSERVER_H

class StandardServer
{

public:

    StandardServer() {}
    ~StandardServer() {}

private:

    int socketNum;

    sockaddr_in serverAddr;

};

#endif // STANDARDSERVER_H