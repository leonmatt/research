/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include "rdmaclient.h"

struct rdma_addrinfo* clearAddrInfo(struct rdma_addrinfo* res)
{

    struct rdma_addrinfo *tmp = NULL;

    while(res) {
 
        tmp = res;
        res = res->ai_next;

        if (tmp->ai_src_addr) {
            free(tmp->ai_src_addr);
            tmp->ai_src_addr = NULL;
        }
        if (tmp->ai_dst_addr) {
            free(tmp->ai_dst_addr);
            tmp->ai_dst_addr = NULL;
        }
        if (tmp->ai_src_canonname) {
            free(tmp->ai_src_canonname);
            tmp->ai_src_canonname = NULL;
        }     
        if (tmp->ai_dst_canonname) {
            free(tmp->ai_dst_canonname);
            tmp->ai_dst_canonname = NULL;
        }
        if (tmp->ai_route) {
            free(tmp->ai_route);
            tmp->ai_route = NULL;
        }
        if (tmp->ai_connect) {
            free(tmp->ai_connect);
            tmp->ai_connect = NULL;
        }
        free(tmp);
        tmp = NULL;     
    }
    res = NULL;

    return res;

}

bool RDMAClient::setupConnection(string server, string portnum)
{

    struct rdma_addrinfo hints = {0};
    struct rdma_addrinfo* res  = NULL;
    struct ibv_qp_init_attr attr = {0};
    struct rdma_cm_id *tmpID;

    struct rdma_conn_param connectionParams = {0};

	int ret = -1;

    uint8_t *recvBuffer = NULL, *sendBuffer = NULL;

    recvBuffer = new (nothrow) uint8_t[1024];
    if (recvBuffer == NULL) {
        cerr << "Failed to allocate the comms buffer." << endl;
        goto BAD_RECV_BUFFER;
    };

    sendBuffer = new (nothrow) uint8_t[1024];
    if (sendBuffer == NULL) {
        cerr << "Failed to allocate the comms buffer." << endl;
        goto BAD_SEND_BUFFER;
    };

    // Set up the type of connection
    hints.ai_port_space = RDMA_PS_TCP;

    // Get the server's addr info
    ret = rdma_getaddrinfo(server.c_str(), portnum.c_str(), &hints, &res);
    if (ret != 0) {
        cerr << "Failed to get addr info." << ret << endl;
        goto BAD_ADDRINFO;
    }

    // Set the communication line details
    attr.cap.max_send_wr = 1;
	attr.cap.max_recv_wr = 1;
	attr.cap.max_send_sge = 1;
	attr.cap.max_recv_sge = 1;
	attr.cap.max_inline_data = 16;
    attr.sq_sig_all = 1;
    attr.qp_context = tmpID;

    // Create the communication endpoint
    ret = rdma_create_ep(&tmpID, res, NULL, &attr);
    if (ret != 0) {
        cerr << "Failed to create endpoint." << errno << endl;
        goto BAD_ENDPOINT;
    }
    

    connectionID = tmpID;

    // Set up receive buffer
    recvMR = rdma_reg_msgs(connectionID, recvBuffer, 16);
    if (recvMR == NULL) {
        ret = -1;
        cerr << "Server failed to register receive buffer";
        goto BAD_CLIENT_CALL;
    }

    // Set up send buffer
    sendMR = rdma_reg_msgs(connectionID, sendBuffer, 16);
    if (sendMR == NULL) {
        ret = -1;
        cerr << "Server failed to register send buffer";
        goto BAD_CLIENT_CALL;
    }

    // Receive connection request response
    ret = rdma_post_recv(connectionID, NULL, recvBuffer, recvMR->length, recvMR);
    if (ret) {
        cerr << "Client failed to post receive work request." << endl;
        goto BAD_CLIENT_CALL;
    }

    // Connect to server
    ret = rdma_connect(connectionID, &connectionParams);
    if (ret != 0) {
        cerr << "Client failed to connect." << endl;
        goto BAD_CLIENT_CALL;
    }

    cout << "Client has connected to the server" << endl << flush;

    goto SUCCESS;

BAD_CLIENT_CALL:

    rdma_destroy_ep(tmpID);

BAD_ENDPOINT:
BAD_ADDRINFO:

    delete sendBuffer;
    sendBuffer = NULL;

BAD_SEND_BUFFER:

    delete recvBuffer;
    recvBuffer = NULL;

BAD_RECV_BUFFER:
SUCCESS:
    
    res = clearAddrInfo(res);

    return (ret == 0);
}

bool RDMAClient::releaseConnection()
{
    if (connectionID != NULL) {
        rdma_disconnect(connectionID);
        connectionID = NULL;
    }

    connectionIP = "";

    if (recvMR != NULL) {
       ibv_dereg_mr(recvMR);
        recvMR = NULL;
    }

    if (sendMR != NULL) {
       ibv_dereg_mr(sendMR);
        sendMR = NULL;
    }
    
    return true;

}

int RDMAClient::receiveMSG(string& msg)
{

    struct ibv_wc workCompletion;

	int ret = rdma_post_recv(connectionID, NULL, recvMR->addr, 16, recvMR);
	if (ret != 0)
        cerr << "Failed to post receive work request." << endl;

    ret = rdma_get_recv_comp(connectionID, &workCompletion);
    if (workCompletion.byte_len > 0) {
        cout << "Message received: " << (char *)recvMR->addr << endl;
        bzero(recvMR->addr, recvMR->length);
    }

    return ret;
}

int RDMAClient::sendMSG(string msg)
{

    int sFlags = 0;

    struct ibv_wc workCompletion;

    //TODO: Get rid of this copy by reading data directly into the MR
    memcpy(sendMR->addr, msg.c_str(), sendMR->length);

	int ret = rdma_post_send(connectionID, NULL, sendMR->addr, 16, sendMR, sFlags);
	if (ret != 0)
        cerr << "Failed to post send work request." << endl;

    ret = rdma_get_send_comp(connectionID, &workCompletion);
    cout << "Message sent: " << (char *)sendMR->addr << endl;

    return ret;
}
