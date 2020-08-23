#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include "instant.h"

/**
 * Usage ./client <server_addr> <server_port>
 */

int main(int argc, char *argv[])
{
	int sock;
	sockaddr_in serv_addr;
#ifdef TEST_WLTB
	char msg[TEST_WLTB_SIZE];
#else
	char msg[MSG_MAX_LEN];
#endif

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
	for (int i = 0; i < MSG_TIME; i++)
	{
		const int sleepTime = 3;
		printf("sleep %d s\n", sleepTime);
		sleep(sleepTime);
		printf("sleep %d s done\n", sleepTime);
		printf("read time: %d\n", i);
#ifdef TEST_WLTB
		sprintf(msg, "111111111 111111111 111111111 00000");
#else
		sprintf(msg, "111111111 111111111 00000");
#endif
		printf("Sending: %s\n", msg);

		if (-1 == write(sock, msg, sizeof(msg) - 1))
		{
			printf("read error\n");
			exit(1);
		}

#ifdef TEST_WLTB_SLEEP_TO_READ
		sleep(1);
#endif

		if (-1 == read(sock, msg, sizeof(msg) - 1))
		{
			printf("read error\n");
			exit(1);
		}
		printf("recv msg: ");
		for (int j = 0; j < sizeof(msg); j++) {
			printf("%c", msg[j]);
		}
		printf("\n");
	}

	close(sock);

	return 0;
}