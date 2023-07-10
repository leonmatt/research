/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BROKER_H
#define BROKER_H

#include <string>
#include <iostream>
#include <memory>

using namespace std;

class StockConnection
{

public:

};

class DerivativeConnection
{

public:

};

class BondConnection
{

public:

};

class ForexConnection
{

public:

};

class Broker
{

public:

    string type;

    shared_ptr<StockConnection> stockConn;
    shared_ptr<StockConnection> derivativeConn;
    shared_ptr<StockConnection> bondConn;
    shared_ptr<StockConnection> forexConn;

};

#endif // BROKER_H