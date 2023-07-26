/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include "rdmaclient.h"

static uint8_t recvBuffers[100][16];
static uint8_t sendBuffers[100][16];

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

    //struct ibv_wc workCompletion;

	int ret = -1;

    uint8_t *recvBuffer = NULL, *sendBuffer = NULL;

    // Set up the type of connection
    hints.ai_port_space = RDMA_PS_TCP;

    // Get the server's addr info
    ret = rdma_getaddrinfo(server.c_str(), portnum.c_str(), &hints, &res);
    if (ret != 0) {
        cerr << "Failed to get addr info." << ret << endl;
        goto BAD_ADDRINFO;
    }

    // Set the communication line details
    memset(&attr, 0, sizeof attr);
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

    // Set up receive buffers
    for (int i = 0; i < 100; i++) {
        recvMRs.push_back(make_shared<struct ibv_mr>(*rdma_reg_msgs(connectionID, recvBuffers[i], 16)));
    }

    cout << "Populated receive memory regions" << endl;

    // Set up send buffer
    /*sendMR = rdma_reg_msgs(connectionID, sendBuffer, 16);
    if (sendMR == NULL) {
        ret = -1;
        cerr << "Server failed to register send buffer";
        goto BAD_SERVER_CALL;
    }*/
    for (int i = 0; i < 100; i++) {
        sendMRs.push_back(make_shared<struct ibv_mr>(*rdma_reg_msgs(connectionID, sendBuffers[i], 16)));
    }

    cout << "Populated send memory regions" << endl;

    // Receive connection request response
    ret = rdma_post_recv(connectionID, NULL, recvBuffers[0], 16, recvMRs[0].get());
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

	/*ret = rdma_post_send(connectionID, NULL, sendBuffer, 16, sendMR, IBV_SEND_INLINE);
	if (ret) {
		perror("rdma_post_send");
	}

    while ((ret = rdma_get_send_comp(connectionID, &workCompletion)) == 0){}
	if (ret < 0) {
		perror("rdma_get_send_comp");
	}

	while ((ret = rdma_get_recv_comp(connectionID, &workCompletion)) == 0) {}
	if (ret < 0)
		perror("rdma_get_recv_comp");
	else
		ret = 0;

    cout << recvBuffer << endl;
    */
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

    /*if (recvMR != NULL) {
       ibv_dereg_mr(recvMR);
        recvMR = NULL;
    }

    if (sendMR != NULL) {
       ibv_dereg_mr(sendMR);
        sendMR = NULL;
    }*/

    recvMRs.clear();
    sendMRs.clear();
    
    return true;

}

int RDMAClient::receiveMSG(string& msg)
{

    /*struct ibv_wc workCompletion;

	int ret = rdma_post_recv(connectionID, NULL, (void *)&msg[0], 16, recvMR);
	if (ret != 0)
        cerr << "Failed to post receive work request." << endl;

    while((ret = rdma_get_recv_comp(connectionID, &workCompletion)) == 0);
    if (workCompletion.byte_len > 0) {
        cout << "Message received: " << msg << endl;
        bzero(recvMR->addr, recvMR->length);
    }*/

    return 0;

}

int RDMAClient::sendData(string fname)
{

    ifstream dataFile(fname);
    if (!dataFile) {
        cerr << "Failed to open file: " << strerror(errno) << endl;
    }

    dataFile.seekg(0, dataFile.end);

    int fsize = (int)dataFile.tellg();

    dataFile.seekg(0, dataFile.beg);

    memcpy(sendBuffers[0], to_string(fsize).c_str(), 16);

    int ret = rdma_post_send(connectionID, NULL, sendBuffers[0], 16, sendMRs[0].get(), IBV_SEND_INLINE);
    if (ret != 0) {
        cerr << "Failed to post send work request: " << errno << endl;
    }

    /*int sFlags = 0;

    struct ibv_wc workCompletion;

    //TODO: Get rid of this copy by reading data directly into the MR
    //memcpy(sendMR->addr, msg.c_str(), sendMR->length);

    int ret = rdma_post_send(connectionID, NULL, (void *)msg.c_str(), 16, sendMR, sFlags);
    if (ret != 0) {
        cerr << "Failed to post send work request: " << errno << endl;
    }

	while ((ret = rdma_get_send_comp(connectionID, &workCompletion)) == 0);
    cout << "Message sent: " << msg << endl;
    */

   /*
       while (dataFile.read(&dataLine[0], 16) || dataFile.gcount()) {
        std::cout.write(&dataLine[0], dataFile.gcount());
        rdmaClient.sendData();
    }*/

    return 0;

}