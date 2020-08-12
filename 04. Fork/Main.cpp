#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "constant.h"

int main(int argint, char *argpt[])
{
	pid_t pid = fork();

	if(0 == pid)
	{
		printf("child process's pid didn't define a value\n");
		// or use return here
		_exit(10);
	}
	else
	{
		printf("This is parent process, child pid: %d\n", pid);

#ifdef TEST_ZOMBIE
		// Zombie process
		printf("Process zombie process\n");
#ifdef TEST_ZOMBIE_WAIT
		{
			int status, wait_process, ret;
			printf("Waiting...\n");
			wait_process = wait(&status);
			ret = WEXITSTATUS(status);
			printf("Wait with wait_process: %d, status: %d, ret: %d\n",
					wait_process, status, ret);
			if(WIFEXITED(status)) {
				printf("Wait successed\n");
			} else {
				printf("Wait with no exit\n");
			}
		}
#endif /* TEST_ZOMBIE_WAIT */

#endif /* TEST_ZOMBIE */
	}
	return 0;
}