/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RDMA_CONNECTION
#define RDMA_CONNECTION

#include <string>

#include <iostream>

#include <netdb.h>

#include <rdma/rdma_verbs.h>
#include <rdma/rdma_cma.h>

using namespace std;

class RDMAConnection {

public:

    string devName;

    RDMAConnection(string&);
    ~RDMAConnection();

    bool setupConnection(string, string);
    void releaseConnection(void);

    //bool setQPState(enum ibv_qp_state);

private:

    // The communication socket
    struct rdma_cm_id *connectionID = NULL;

    // The receive and send buffers
    struct ibv_mr* recvMR = NULL;
    struct ibv_mr* sendMR = NULL;

    // The IP that we connected to or binded to
    string connectionIP;

};


#endif