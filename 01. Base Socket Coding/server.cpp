#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/**
 * Usage ./server <server_port>
 */

int main (int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;
	int res;

	/*
	struct sockaddr_in {
	short int sin_family;                      // Address family 
	unsigned short int sin_port;       	   // Port number 
	struct in_addr sin_addr;               	   // Internet address 32-bit IPv4 address
	unsigned char sin_zero[8];         	   // Same size as struct sockaddr 
	};
	*/
	sockaddr_in serv_addr;
	sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;
	char msg[] = "Hello world!";

	if (2 != argc)
	{
		printf("argv[0]: %s\n", argv[0]);
		exit(1);
	}

	// Step 1: create socket
	// int socket(int af, int type, int protocol)
	// af		:==AF_INET(Address Family Internet)
	// type 	:SOCK_STREAM/SOCK_DGRAM
	// protocol	:IPPROTO_TCP/IPPTOTO_UDP
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	printf("serv_sock = %d\n", serv_sock);
	if (-1 == serv_sock)
	{
		exit(1);
	}

	// Step 2: bind socket to ADDR:PORT
	memset(&serv_addr, 0, sizeof(serv_addr));//initialize serv_addr
	serv_addr.sin_family = AF_INET;
	//htonl:host to net unsigned long
	//INADDR_ANY:0.0.0.0,localhost whole device's IP
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//htons:host to network short
	serv_addr.sin_port = htons(atoi(argv[1]));
	printf("bind\n");
	//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
	//bind the descriptor(sockfd) and sock.
	//sockfd: descriptor
	//addr  : A pointer point to the address sockfd binding with.
	if (-1 == bind(serv_sock, (sockaddr *)&serv_addr, sizeof(serv_addr)))
	{
		exit(1);
	}

	// Step 3: start listening
	printf("listen\n");
	if (-1 == listen(serv_sock, 5))
	{
		exit(1);
	}

	// Step 4: accept connection req (wait for req)
	clnt_addr_size = sizeof(clnt_addr);
	/*int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);*/
	//receive information from an established connection
	clnt_sock = accept(serv_sock, (sockaddr *)&clnt_addr, &clnt_addr_size);
	printf("clnt_sock = %d\n", clnt_sock);
	if (-1 == clnt_sock)
	{
		exit(1);
	}

	write(clnt_sock, msg, sizeof(msg));
	close(clnt_sock);
	close(serv_sock);

	return 0;
}
