#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

int main(int argi, char *arga[])
{
	fd_set reads, temps;
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_addr_sz;
	struct timeval timeout;
	int serv_skt, clnt_skt, fd_max, fd_num;
	constexpr int READ_BUF_SZ = 100;
	char read_buf[READ_BUF_SZ] = {0};

	// sanity check
	if(argi < 2)
	{
		printf("Plz ./main <port>\n");
		exit(-1);
	}

	serv_skt = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(arga[1]));

	if(-1 == bind(serv_skt, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) {
		printf("bind error\n");
		exit(-1);
	}

	if(-1 == listen(serv_skt, 5)) {
		printf("listen error\n");
		exit(-1);
	}

	FD_ZERO(&reads);
	// listen to serv_skt first
	FD_SET(serv_skt, &reads);
	fd_max = serv_skt;

	while(1)
	{
		temps = reads;
		// listen timeout
		// control select timeout frequency
		timeout.tv_sec = 2;
		timeout.tv_usec = 0;

		printf("select - doing select\n");
		if (-1 == (fd_num = select(fd_max + 1, &temps, 0, 0, &timeout)))
		{
			break;
		}
		printf("select - select done\n");

		if (0 == fd_num)
		{
			continue;
		}

		for (int i = 0; i < fd_max + 1; i++)
		{
			// check is set listen
			if (FD_ISSET(i, &temps))
			{
				// listen to serv_skt first
				// connection comein, fd become readable
				if (i == serv_skt)
				{
					printf("serv_skt %d: connection comein\n", serv_skt);
					clnt_addr_sz = sizeof(clnt_addr);
					clnt_skt = accept(serv_skt, (struct sockaddr *)&clnt_addr, &clnt_addr_sz);
					// set clnt_skt listen
					FD_SET(clnt_skt, &reads);
					if (fd_max < clnt_skt)
					{
						fd_max = clnt_skt;
					}
					printf("serv_skt %d: connection comein at %d\n", serv_skt, clnt_skt);
				}
				else // clnt_skt readable
				{
					printf("clnt_skt %d: readable\n", i);
					int msg_sz = read(i, &read_buf, READ_BUF_SZ);
					if (0 == msg_sz)
					{
						printf("clnt_skt %d: size 0\n", i);
						close(i);
					}
					else
					{
						constexpr char writeBack[] = "writeBack from server\n";
						printf("clnt_skt %d: recv: %s\n", i, read_buf);
						write(i, writeBack, sizeof(writeBack));
					}
				}
			}
		}
	}

	return 0;
}