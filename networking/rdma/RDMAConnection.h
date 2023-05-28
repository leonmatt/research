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
    string devName = "";
    struct ibv_device*  device  = NULL;
    struct ibv_context* context = NULL;

    bool setupConnection(const string&);
    void releaseConnection(void);

private:
    bool setupContext(const string&);

};


#endif