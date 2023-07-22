/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include <memory>

using namespace std;

class TSMediator;

#ifndef TRADINGENGINE_H
#define TRADINGENGINE_H

class TradingEngine
{

public:

    shared_ptr<TSMediator> mediator;

    TradingEngine() {}
    ~TradingEngine() {}

};

#endif // TRADINGENGINE_H