/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RDMA_CONNECTION
#define RDMA_CONNECTION

#include <string>

#include <iostream>

#include <infiniband/verbs.h>

using namespace std;

class RDMAConnection {

public:

    string devName;

    RDMAConnection(string&);

    bool setupConnection(void);
    void releaseConnection(void);

private:

    // The hardware device
    struct ibv_device*  device      = NULL;

    // The hardware device context
    struct ibv_context* context     = NULL;

    // The protection domain
    struct ibv_pd* protectionDomain = NULL;

    // The completion queue
    struct ibv_cq* completionQueue  = NULL;

    bool setupContext(void);
    void releaseContext(void);

    bool setupPD(void);
    void releasePD(void);

    bool setupCQ(void);
    void releaseCQ(void);

};


#endif