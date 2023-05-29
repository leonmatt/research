CPP = g++
CFLAGS = -std=c++11 -Wall -pedantic 
VFLAGS = -lrdmacm -libverbs

all: RDMAConnection client server

clean:
	rm *.o
	rm client
	rm server

RDMAConnection: RDMAConnection.cpp
	$(CPP) $(CFLAGS) -c RDMAConnection.cpp $(VFLAGS)

client: client.cpp
	$(CPP) $(CFLAGS) -c client.cpp 
	$(CPP) $(CFLAGS) -o client client.o RDMAConnection.o $(VFLAGS)

server: server.cpp
	$(CPP) $(CFLAGS) -c server.cpp 
	$(CPP) $(CFLAGS) -o server server.o RDMAConnection.o $(VFLAGS)
