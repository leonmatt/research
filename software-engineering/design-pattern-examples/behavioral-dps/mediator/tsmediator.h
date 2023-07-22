/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include <memory>

#include "tradingengine.h"
#include "orderengine.h"

using namespace std;

#ifndef TSMEDIATOR_H
#define TSMEDIATOR_H

class TSMediator
{

public:

    shared_ptr<TradingEngine> tEngine;
    shared_ptr<OrderEngine> oEngine;

    TSMediator() {}
    ~TSMediator() {}

};

#endif // TSMEDIATOR_H