/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include "RDMAConnection.h"

bool RDMAConnection::setupConnection(const string& deviceName)
{
    bool ret = setupContext(deviceName);

    cout << "Device Set Up: " << deviceName << endl;

    return ret;
}

void RDMAConnection::releaseConnection(void)
{

    device  = NULL;
    context = NULL;

}

bool RDMAConnection::setupContext(const string& deviceName)
{

    int nDevs = 0;
    struct ibv_device** devices = ibv_get_device_list(&nDevs);

    // Loop through and get the device that we picked
    string tmpDeviceName;
    for (int i = 0; i < nDevs; i++) {
    
        tmpDeviceName = ibv_get_device_name(devices[i]);
        if (devName.compare(tmpDeviceName) == 0) {

            device  = devices[i];
            context = ibv_open_device(device);
            devName = tmpDeviceName;
            i = nDevs;
        }

    }

    // Release the device list because we no longer need it
    ibv_free_device_list(devices);

    return (context != NULL);

}

