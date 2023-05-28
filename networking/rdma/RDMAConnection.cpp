/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include "RDMAConnection.h"

// RDMAConnection Constructor
RDMAConnection::RDMAConnection(string& deviceName)
{

    devName = deviceName;

}

// RDMAConnection Destructor
RDMAConnection::~RDMAConnection()
{

    releaseConnection();

}


// Set up a device connection
bool RDMAConnection::setupConnection(void)
{

    cout << "Setting up connection for device: " << devName << endl;

    bool ret = setupContext();
    if (ret == false) {
        cout << "Setup context failed. Exiting..." << endl;
        goto END;
    }
    cout << "Finished setting up context" << endl;

    ret = setupPD();
    if (ret == false){
        cout << "Setup PD failed. Exiting..." << endl;
        goto BAD_PD;
    }
    cout << "Finished setting up protection domain" << endl;

    ret = setupCQ();
    if (ret == false){
        cout << "Setup CQ failed. Exiting..." << endl;
        goto BAD_CQ;
    }
    cout << "Finished setting up completion queue" << endl;

    ret = setupQP();
    if (ret == false){
        cout << "Setup QP failed. Exiting..." << endl;
        goto BAD_QP;
    }
    cout << "Finished setting up  queue pair" << endl;

    cout << "Device Registered: " << devName << endl << endl;
    goto END;

BAD_QP:
    releaseCQ();

BAD_CQ:
    releasePD();

BAD_PD:
    releaseContext();

END:
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
    if (context != NULL)
    ibv_close_device(context);
    context = NULL;

}

// Release a device connection
void RDMAConnection::releaseConnection(void)
{

    device           = NULL;
    context          = NULL;

    releasePD();

    releaseCQ();

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

    if (protectionDomain != NULL)
        ibv_dealloc_pd(protectionDomain);
    protectionDomain = NULL;
}

// Set up a completion queue for the device
bool RDMAConnection::setupCQ(void)
{

    completionQueue = ibv_create_cq(context, 100, NULL, NULL, 0);
    return (completionQueue != NULL);

}

// Release the completion queue
void RDMAConnection::releaseCQ(void)
{
    if (completionQueue != NULL)
        ibv_destroy_cq(completionQueue);
    completionQueue = NULL;
}

// Set up a queue pair for the connection
bool RDMAConnection::setupQP(void)
{

    struct ibv_qp_init_attr qpAttrs;
    memset(&qpAttrs, 0, sizeof(ibv_qp_init_attr));

    qpAttrs.send_cq = completionQueue;
    qpAttrs.recv_cq = completionQueue;
    qpAttrs.cap.max_send_wr  = 1;
    qpAttrs.cap.max_recv_wr  = 1;
    qpAttrs.cap.max_send_sge = 1;
    qpAttrs.cap.max_recv_sge = 1;
    //Use reliable connection
    qpAttrs.qp_type = IBV_QPT_RC;
    qpAttrs.sq_sig_all = 1;

    queuePair = ibv_create_qp(protectionDomain, &qpAttrs);
    return (queuePair != NULL);

}

// Release the queue pair
void RDMAConnection::releaseQP(void)
{
    if (queuePair != NULL)
        ibv_destroy_qp(queuePair);
    queuePair = NULL;
}