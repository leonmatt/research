/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RUNTIME_H
#define RUNTIME_H

// Concrete Runtime Class

class Runtime
{

public:

    static Runtime *getRuntime()
    {

        if (currentRuntime == nullptr) {
            currentRuntime = new Runtime();
        }

        return currentRuntime;

    }

    ~Runtime() {}

private:

    static Runtime *currentRuntime;

    Runtime()  {}
    Runtime(const Runtime &copy) {}

};

Runtime *Runtime::currentRuntime = nullptr;

#endif // RUNTIME_H