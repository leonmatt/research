/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef HARDWARE_H
#define HARDWARE_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class HardwareDevice
{

public:

    virtual void build() {}

};

class XEONCPU : HardwareDevice
{

public:

    string name;

    XEONCPU() {}
    ~XEONCPU() {}

    void build() override
    {

        cout << "We built a XEON CPU" << endl;

    }

};

class CoreCPU : HardwareDevice
{

public:

    string name;

    CoreCPU() {}
    ~CoreCPU() {}

    void build() override
    {

        cout << "We built a Core CPU" << endl;

    }

};

class E810NIC : HardwareDevice
{

public:

    string name;

    E810NIC() {}
    ~E810NIC() {}

    void build() override
    {

        cout << "We built an E810 NIC" << endl;

    }

};

class IPUNIC : HardwareDevice
{

public:

    string name;

    IPUNIC() {}
    ~IPUNIC() {}

    void build() override
    {

        cout << "We built an IPU NIC" << endl;

    }

};

class HardwareGroup
{

public:

    vector<shared_ptr<HardwareDevice>> deviceVector;

    HardwareGroup() {}
    ~HardwareGroup() {}

    void build()
    {

        for (shared_ptr<HardwareDevice> i : deviceVector)
            i->build();

        deviceVector.clear();

    }

    void addDevice(shared_ptr<HardwareDevice> device)
    {
        deviceVector.push_back(device);
    }

    void removeDevice()
    {
        deviceVector.pop_back();
    }

};

shared_ptr<HardwareDevice> getHardwareDevice(string kind)
{

    HardwareDevice *ptr = NULL;

    if (kind.compare("XEON") == 0)
        ptr = (HardwareDevice *)new XEONCPU();

    else if (kind.compare("Core") == 0)
        ptr = (HardwareDevice *)new CoreCPU();

    if (kind.compare("E810") == 0)
        ptr = (HardwareDevice *)new E810NIC();

    else if (kind.compare("IPU") == 0)
        ptr = (HardwareDevice *)new IPUNIC();

    shared_ptr<HardwareDevice> ret(ptr);

    return ret;

}

#endif // HARDWARE_H