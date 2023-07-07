/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include "hardware.h"

int main(void)
{

    // Allocate Hardware Group
    HardwareGroup *myGroup = new HardwareGroup();

    // Allocate Hardware Devices
    myGroup->addDevice(getHardwareDevice("XEON"));
    myGroup->addDevice(getHardwareDevice("Core"));
    myGroup->addDevice(getHardwareDevice("E810"));
    myGroup->addDevice(getHardwareDevice("IPU"));

    // Build the Hardware Devices
    myGroup->buildAllDevices();

    // Remove the Hardware Group
    delete myGroup;

    return 0;

}