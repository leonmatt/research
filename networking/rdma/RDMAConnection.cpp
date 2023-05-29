/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include "RDMAConnection.h"

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

bool RDMAConnection::setupConnection(string server, string portnum)
{

	struct rdma_addrinfo hints = {0};
    struct rdma_addrinfo* res  = NULL;
	struct ibv_qp_init_attr attr = {0}, initAttr = {0};
    struct ibv_qp_attr qpAttr = {};

    struct rdma_conn_param connectionParams = {0};
	
    struct ibv_mr *recvMR = NULL, *sendMR = NULL;

    bool isServer = false;

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

    // Determine if this is server or client
    if (server.compare("0.0.0.0") == 0)
        isServer = true;

    // Set up the type of connection
    if (isServer) {
        hints.ai_flags      = RAI_PASSIVE;
        hints.ai_qp_type    = IBV_QPT_RC;
    }
    hints.ai_port_space = RDMA_PS_TCP;

    // Get the server's addr info
    ret = rdma_getaddrinfo(server.c_str(), portnum.c_str(), &hints, &res);
    if (ret != 0) {
        cerr << "Failed to get addr info." << ret << endl << flush;
        goto BAD_ADDRINFO;
    }

    // Set the communication line details
    attr.cap.max_send_wr = 1;
	attr.cap.max_recv_wr = 1;
	attr.cap.max_send_sge = 1;
	attr.cap.max_recv_sge = 1;
	attr.cap.max_inline_data = 16;
    attr.sq_sig_all = 1;

    if (!isServer) {
        attr.qp_context = connectionID;
    }

    // Create the communication endpoint
    ret = rdma_create_ep(&connectionID, res, NULL, &attr);
        if (ret != 0) {
            cerr << "Failed to create endpoint." << errno << endl;
            goto BAD_ENDPOINT;
        }

    if (isServer) {

        // Set the endpoint to listen
        ret = rdma_listen(connectionID, 1);
        if (ret != 0) {
            cerr << "Server failed to listen." << endl;
            goto BAD_SERVER_CALL;
        }

        // Receive a request to connect
        ret = rdma_get_request(connectionID, &connectionID);
        if (ret != 0) {
            cerr << "Server failed to get request from listening." << endl;
            goto BAD_SERVER_CALL;
        }
        
        // Get the details of the queue pair from the incoming connection
        ret = ibv_query_qp(connectionID->qp, &qpAttr, IBV_QP_CAP, &initAttr);
        if (ret != 0) {
            cerr << "Server failed to query the QP." << endl;
            goto BAD_SERVER_CALL;
        }

        // Set up receive buffer
        recvMR = rdma_reg_msgs(connectionID, recvBuffer, 1024);
        if (recvMR == NULL) {
            ret = -1;
            cerr << "Server failed to register receive buffer";
            goto BAD_SERVER_CALL;
        }

        // Set up send buffer
        sendMR = rdma_reg_msgs(connectionID, sendBuffer, 1024);
        if (sendMR == NULL) {
            ret = -1;
            cerr << "Server failed to register send buffer";
            goto BAD_SERVER_CALL;
        }

        // Receive incoming connection request
	    ret = rdma_post_recv(connectionID, NULL, recvBuffer, 1024, recvMR);
	    if (ret != 0) {
            cerr << "Server failed to receive connection message";
	    	goto BAD_SERVER_CALL;
	    }        

        // Accept the connection
        ret = rdma_accept(connectionID, &connectionParams);
        if (ret != 0) {
            cerr << "Server failed to accept." << endl;
            goto BAD_SERVER_CALL;
        }

        cout << "Server has connected to client" << endl << flush;

    }
    
    else {

        // Set up receive buffer
        recvMR = rdma_reg_msgs(connectionID, recvBuffer, 1024);
        if (recvMR == NULL) {
            ret = -1;
            cerr << "Server failed to register receive buffer";
            goto BAD_SERVER_CALL;
        }

        // Set up send buffer
        sendMR = rdma_reg_msgs(connectionID, sendBuffer, 1024);
        if (sendMR == NULL) {
            ret = -1;
            cerr << "Server failed to register send buffer";
            goto BAD_SERVER_CALL;
        }

        // Receive connection request response
	    ret = rdma_post_recv(connectionID, NULL, recvBuffer, 16, recvMR);
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

    }

    goto SUCCESS;

BAD_CLIENT_CALL:
BAD_SERVER_CALL:

    rdma_destroy_ep(connectionID);

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

void RDMAConnection::releaseConnection(void)
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
    
}