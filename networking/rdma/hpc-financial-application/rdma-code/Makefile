CPP = g++
CFLAGS = -std=c++11 -Wall -pedantic 
VFLAGS = -lrdmacm -libverbs

all: RDMAConnection client server

	mkdir -p ../bin
	cp rdma_client ../bin
	cp rdma_server ../bin

clean:
	rm *.o
	rm rdma_client
	rm rdma_server

RDMAConnection: RDMAConnection.cpp
	$(CPP) $(CFLAGS) -c RDMAConnection.cpp $(VFLAGS)

client: client.cpp
	$(CPP) $(CFLAGS) -c client.cpp 
	$(CPP) $(CFLAGS) -o rdma_client client.o RDMAConnection.o $(VFLAGS)

server: server.cpp
	$(CPP) $(CFLAGS) -c server.cpp 
	$(CPP) $(CFLAGS) -o rdma_server server.o RDMAConnection.o $(VFLAGS)
