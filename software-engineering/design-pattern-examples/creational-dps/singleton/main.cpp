/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include "runtime.h"

#include <iostream>

using namespace std;

int main(void)
{

    Runtime *cRuntime1 = Runtime::getRuntime();
    Runtime *cRuntime2 = Runtime::getRuntime();

    cout << "The first  runtime points to the Runtime at: " << cRuntime1 << endl;
    cout << "The second runtime points to the Runtime at: " << cRuntime2 << endl;

    // Release Runtime
    delete cRuntime1;

    return 0;

}