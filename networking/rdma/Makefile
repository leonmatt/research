CC = gcc
CFLAGS = -Wall -pedantic
VFLAGS = -lrdmacm -libverbs

all: hello_world

clean:
	rm helloworld

hello_world: hello_world.c
	$(CC) $(CFLAGS) hello_world.c -o helloworld $(VFLAGS)