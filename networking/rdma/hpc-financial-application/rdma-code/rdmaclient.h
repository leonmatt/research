/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include <string>

#include <iostream>

#include <netdb.h>

#include <rdma/rdma_verbs.h>
#include <rdma/rdma_cma.h>

using namespace std;

#ifndef RDMACLIENT_H
#define RDMACLIENT_H

class RDMAClient
{

public:

    string devName;

    RDMAClient(string deviceName)
    {

        devName = deviceName;

    }
    ~RDMAClient() 
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



#endif // RDMACLIENT_H