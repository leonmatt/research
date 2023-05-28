CPP = g++
CFLAGS = -std=c++11 -Wall -pedantic
VFLAGS = -lrdmacm -libverbs

all: RDMAConnection Main

clean:
	rm *.o
	rm main

RDMAConnection: RDMAConnection.cpp
	$(CPP) $(CFLAGS) -c RDMAConnection.cpp $(VFLAGS)

Main: main.cpp
	$(CPP) $(CFLAGS) -c main.cpp 
	$(CPP) $(CFLAGS) -o main main.o RDMAConnection.o $(VFLAGS)
