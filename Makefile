CFLAGS=-w

all: chat
	bin
	g++ $(CFLAGS) build/server.o -o bin/server
	g++ $(CFLAGS) build/client.o -o bin/client

chat: server.o client.o
	mkdir build
	mv server.o build/
	mv client.o build/

server.o: 
	$(CC) -c $(CFLAGS) src/server.cc

client.o:
	$(CC) -c $(CFLAGS) src/client.cc

clean:
	rm -rf build/ bin/
