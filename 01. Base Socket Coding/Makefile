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

server.o : server.cpp
	cc -c server.cpp

client.o : $(src-client)
	cc -c $(src-client)

clean:
	rm server client $(obj)