src-common = instant.h
obj-server = server.o
src-server = server.cpp
obj-client = client.o
src-client = client.cpp
obj = $(obj-server) $(obj-client)

all : server client

server : $(obj-server) $(src-server)
	g++ -o server $(obj-server)

client : $(obj-client) $(src-client)
	g++ -o client $(obj-client)

server.o : $(src-server) $(src-common)
	cc -c $(src-server)

client.o : $(src-client) $(src-common)
	cc -c $(src-client)

clean:
	rm server client $(obj)