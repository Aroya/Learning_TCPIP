all : server client

server : server.cpp
	cc -o server server.cpp

client : client.cpp instant.h
	cc -o client client.cpp

clean :
	rm server client