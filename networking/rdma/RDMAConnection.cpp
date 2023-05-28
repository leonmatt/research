/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include "RDMAConnection.h"

RDMAConnection::RDMAConnection(string& deviceName)
{

    devName = deviceName;

}

// Set up a device connection
bool RDMAConnection::setupConnection(void)
{

    cout << "Setting up connection for device: " << devName << endl;

    bool ret = setupContext();
    if (ret == false) {
        cout << "Setup context failed. Exiting..." << endl;
        return ret;
    }
    cout << "Finished setting up context" << endl;

    ret = setupPD();
    if (ret == false){
        cout << "Setup PD failed. Exiting..." << endl;
        return ret;
    }
    cout << "Finished setting up protection domain" << endl;

    cout << "Device Registered: " << devName << endl << endl;

    return ret;
}

// Open a device context so the device can be used
bool RDMAConnection::setupContext(void)
{

    int nDevs = 0;
    struct ibv_device** devices = ibv_get_device_list(&nDevs);
    if (devices == NULL)
        return (devices != NULL);

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

// Release a device context
void RDMAConnection::releaseContext(void)
{

    ibv_close_device(context);

}

// Release a device connection
void RDMAConnection::releaseConnection(void)
{

    device           = NULL;
    context          = NULL;

    releasePD();

    cout << "Finished releasing resources for: " << devName << endl;

}

// Set up a protection domain for the host machine
bool RDMAConnection::setupPD(void)
{

    protectionDomain = ibv_alloc_pd(context);

    return (protectionDomain != NULL);

}

// Release the protection domain
void RDMAConnection::releasePD(void)
{

    ibv_dealloc_pd(protectionDomain);
    protectionDomain = NULL;
}

// Set up a completion queue for the device
bool RDMAConnection::setupCQ(void)
{

    //completionQueue = ibv_alloc_pd(context);

    //return (completionQueue != NULL);

    return true;

}

// Release the completion queue
void RDMAConnection::releaseCQ(void)
{

    //ibv_dealloc_pd(completionQueue);
    //completionQueue = NULL;
}