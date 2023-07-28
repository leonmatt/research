/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include <iostream>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#ifndef STANDARDCLIENT_H
#define STANDARDCLIENT_H

class StandardClient
{

public:

    StandardClient() {}
    ~StandardClient() {}

private:

    int socketNum;

    sockaddr_in serverAddr;

};

#endif // STANDARDCLIENT_H