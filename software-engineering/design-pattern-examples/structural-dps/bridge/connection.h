/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <iostream>

#include "message.h"

using namespace std;

// Abstract Interface
class Connection
{

public:

    virtual void sendMessage(string msg) {};

};

// Concrete Interface
class NetworkConnection : Connection
{

public:

    NetworkConnection(MessageInterface *interface) 
    {
        msgIntf = interface;
    }
    ~NetworkConnection() 
    {
        delete msgIntf;
    }

    void sendMessage(string msg) override
    {
        msgIntf->sendMessage(msg);
    }

private:

    MessageInterface *msgIntf;

};

// Concrete Interface
class DatabaseConnection : Connection
{

public:

    DatabaseConnection() {}
    ~DatabaseConnection() {}

    void sendMessage(string msg) override
    {
        msgIntf->sendMessage(msg);
    }

private:

    MessageInterface *msgIntf;

};


// Returns a Network Connection
NetworkConnection *getNetworkConnection(string protocol)
{

    // The kind of network protocol
    MessageInterface *msgIntf = NULL;
    
    if (protocol == "GRPC")
       msgIntf = (MessageInterface *)new GRPCInterface();
    
    else if (protocol == "MPI")
        msgIntf = (MessageInterface *)new MPIInterface();
    
    return new NetworkConnection(msgIntf);

};


// Returns a Network Connection
DatabaseConnection *getDatabaseConnection()
{

    return new DatabaseConnection();

}

// Returns a new connection
Connection *getConnection(string kind, string protocol)
{

    Connection *ret = NULL;

    if (kind == "Network")
        ret = (Connection *)getNetworkConnection(protocol);
    
    else if (kind == "Database")
        ret = (Connection *)getDatabaseConnection();

    return ret;

}

#endif // CONNECTION_H