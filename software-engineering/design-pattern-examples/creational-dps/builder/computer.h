/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>

#include <iostream>

#include "CPU.h"
#include "MB.h"
#include "RAM.h"
#include "DISK.h"
#include "PS.h"

using namespace std;

class Computer
{

public:

    string description;

    CPU *cCPU;
    MB *cMB;
    RAM *cRAM;
    DISK *cDISK;
    PS *cPS;

};

// Abstract Computer Builder Class
class ComputerBuilder
{

public:

    string computerBrand;

};

// Concrete Computer Builder Class
class IntelComputerBuilder : public ComputerBuilder
{

public:



};

// Director Computer Store Class
class ComputerStore
{

public:

    IntelComputerBuilder *intelSupplier;

};

#endif // COMPUTER_H