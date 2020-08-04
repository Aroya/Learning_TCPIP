#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "instant.h"

/**
 * Usage ./server <server_port>
 */

int main (int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;
	int res;

	sockaddr_in serv_addr;
	sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;
	char msg[MSG_MAX_LEN];

	if (2 != argc)
	{
		printf("argv[0]: %s\n", argv[0]);
		exit(1);
	}

	// Step 1: create socket
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	printf("serv_sock = %d\n", serv_sock);
	if (-1 == serv_sock)
	{
		exit(1);
	}

	// Step 2: bind socket to ADDR:PORT
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));
	printf("bind\n");
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
	for (int i = 0; i < MSG_TIME; i++)
	{
		int str_len;
		int read_time = 0;

		// accept connection
		clnt_sock = accept(serv_sock, (sockaddr *)&clnt_addr, &clnt_addr_size);
		printf("clnt_sock = %d\n", clnt_sock);
		if (-1 == clnt_sock)
		{
			exit(1);
		}
		// read until EOF
		while(0 != (str_len = read(clnt_sock, msg, MSG_MAX_LEN))) {
			printf("Received msg: %s\n", msg);
			sprintf(msg, "Hello! msg_time: %d, %d", i, read_time++);
			printf("Sending msg: %s\n", msg);
			write(clnt_sock, msg, sizeof(msg));
		}
		close(clnt_sock);
	}
	close(serv_sock);

	return 0;
}