/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include "computer.h"

int main(void)
{

    ComputerStore *myIntelCB = new ComputerStore();

    Computer *myNewPC = myIntelCB->getComputer("Intel");
    if (myNewPC != NULL) {
        cout << "We got a new PC!" << endl;
    }

    delete myNewPC;

    delete myIntelCB;

}

