/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef TARGETADAPTER_H
#define TARGETADAPTER_H

#include <iostream>
#include <string>

#include "target.h"

using namespace std;

class TargetAdapter : Target
{

public:

    Target *adaptedTarget;

    TargetAdapter(Target *Target)
    {
        adaptedTarget = Target;
    }
    ~TargetAdapter() {}

    void setTargetValue(string value)
    {

        adaptedTarget->setTargetValue(stoi(value));

    }

};

#endif // TARGETADAPTER_H