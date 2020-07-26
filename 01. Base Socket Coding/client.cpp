#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

/**
 * Usage ./client <server_addr> <server_port>
 */

int main(int argc, char *argv[])
{
	int sock;
	sockaddr_in serv_addr;
	char msg[30];

	if (3 != argc)
	{
		printf("port: %s\n", argv[0]);
		exit(1);
	}

	// Step 1 create socket
	printf("socket\n");
	if (-1 == (sock = socket(PF_INET, SOCK_STREAM, 0)))
	{
		printf("sock error\n");
		exit(1);
	}

	// Step 2 conect to socket
	printf("connect\n");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));
	if (-1 == connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)))
	{
		printf("connect error\n");
		exit(1);
	}

	// Step 3 read from socket
	printf("read\n");
	if (-1 == read(sock, msg, sizeof(msg) - 1))
	{
		printf("read error\n");
		exit(1);
	}

	printf("recv msg: %s\n", msg);
	close(sock);

	return 0;
}