/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>

#include <iostream>

#include <vector>

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

    Computer() {}
    ~Computer() {

        delete cCPU;
        delete cMB;
        delete cRAM;
        delete cDISK;
        delete cPS;

    }

};

// Abstract Computer Builder Class
class ComputerBuilder
{

public:

    string computerBrand;

    virtual void buildComputer() {}

};

// Concrete Computer Builder Class
class IntelComputerBuilder : public ComputerBuilder
{

public:

    IntelComputerBuilder() {}
    ~IntelComputerBuilder() {}

    void buildComputer() override {

        Computer *newComp = new Computer();

        newComp->cCPU = getCPU();
        newComp->cMB = getMB();
        newComp->cRAM = getRAM();
        newComp->cPS = getPS();
        newComp->cDISK = getDISK();

        computersInStock.push_back(newComp);

    }

    Computer *getComputer() {

        Computer *ret = computersInStock[0];

        computersInStock.pop_back();

        return ret;

    }

private:

    vector<Computer *> computersInStock;

    CPU *getCPU(){
        return new CPU();
    }

    MB *getMB(){
        return new MB();
    }

    RAM *getRAM(){
        return new RAM();
    }

    PS *getPS(){
        return new PS();
    }

    DISK *getDISK(){
        return new DISK();
    }

};

// Director Computer Store Class
class ComputerStore
{

public:

    IntelComputerBuilder *intelSupplier;

    ComputerStore() {

        intelSupplier = new IntelComputerBuilder();

    }

    ~ComputerStore() {

        delete intelSupplier;

    }

    Computer *getComputer(string computerBrand) {

        Computer *ret = NULL;

        if (computerBrand.compare("Intel") == 0) {

            intelSupplier->buildComputer();

            ret = intelSupplier->getComputer();

        }

        return ret;

    }

};

#endif // COMPUTER_H