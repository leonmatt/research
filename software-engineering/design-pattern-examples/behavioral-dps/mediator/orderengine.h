/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include <memory>

using namespace std;

class TSMediator;

#ifndef ORDERENGINE_H
#define ORDERENGINE_H

class OrderEngine
{

public:

    shared_ptr<TSMediator> mediator;

    OrderEngine() {}
    ~OrderEngine() {}

};

#endif // ORDERENGINE_H