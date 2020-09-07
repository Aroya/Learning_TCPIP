#include <sys/epoll.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * 仅示意如何使用，不保证能够正常运行
 */

constexpr int SKTFD = 0xff;
constexpr int WAIT_TIMEOUT_UNTIL_RECV = -1;
constexpr int WAIT_TIMEOUT = 1000;

int main(int argi, char *arga[])
{
	int epollFd = epoll_create(0);
	struct epoll_event epollevt;
	epollevt.events = EPOLLIN | EPOLLET;
	epollevt.data.fd = SKTFD;
	if (!epoll_ctl(epollFd, 
					EPOLL_CTL_ADD,
					SKTFD,
					&epollevt))
	{
		exit(1);
	}

	while(epoll_wait(epollFd,
					&epollevt,
					1,
					WAIT_TIMEOUT_UNTIL_RECV))
	{
		printf("do job here\n");
		// do job here
	}
	close(epollFd);
	return 0;
}