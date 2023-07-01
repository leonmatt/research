/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef SERVER_H
#define SERVER_H

// Abstract Connection Class
class Connection
{

public:

    virtual Connection *clone() const = 0;

    int socketVal;

};

// Concrete Connection Clss
class ServerConnection : public Connection
{

public:

    //ServerConnection(int inputSocket)
    ServerConnection(int inputSocket)
    {

        socketVal = inputSocket;

    }
    ~ServerConnection() {}

    Connection *clone() const override
    {
        return new ServerConnection(*this);
    }

};

#endif // SERVER_H