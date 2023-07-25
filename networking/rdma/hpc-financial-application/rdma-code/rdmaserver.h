/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include <cerrno>

#include <string>

#include <iostream>

#include <netdb.h>

#include <rdma/rdma_verbs.h>
#include <rdma/rdma_cma.h>

using namespace std;

#ifndef RDMASERVER_H
#define RDMASERVER_H

class RDMAServer
{

public:

    string devName;

    RDMAServer(string deviceName)
    {

        devName = deviceName;

    }
    ~RDMAServer()
    {

        releaseConnection();

    }

    bool setupConnection(string, string);
    bool releaseConnection();

    int receiveMSG(string& msg);
    int sendMSG(string msg);


private:

    // The communication socket
    struct rdma_cm_id *connectionID = NULL;

    // The receive and send buffers
    struct ibv_mr* recvMR = NULL;
    struct ibv_mr* sendMR = NULL;

    // The IP that we connected to or binded to
    string connectionIP;

};



#endif // RDMASERVER_H