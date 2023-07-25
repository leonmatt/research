CPP = g++
CFLAGS = -g -std=c++11 -Wall -pedantic 
VFLAGS = -lrdmacm -libverbs

all: client server
	mkdir -p ../bin
	cp rdma_client ../bin/
	cp rdma_server ../bin/

clean:
	rm rdma_client
	rm rdma_server

client: client.cpp
	$(CPP) $(CFLAGS) -o rdma_client client.cpp rdmaclient.cpp $(VFLAGS)

server: server.cpp
	$(CPP) $(CFLAGS) -o rdma_server server.cpp rdmaserver.cpp $(VFLAGS)
