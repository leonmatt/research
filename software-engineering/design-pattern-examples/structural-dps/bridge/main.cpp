/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include "connection.h"

int main(void)
{

    // Set up NetworkConnections
    Connection *connectionGRPC = getConnection("Network", "GRPC");
    Connection *connectionMPI = getConnection("Network", "MPI");

    connectionGRPC->sendMessage("Hello World!");
    connectionMPI->sendMessage("Hello World!");

    delete connectionGRPC;
    delete connectionMPI;

    return 0;

}