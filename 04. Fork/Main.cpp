#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "constant.h"

#if (defined TEST_ZOMBIE_SIGNAL) || (defined TEST_ZOMBIE_SIGACTION)
#include <signal.h>
// signal handle
// TODO: what does (int sig) mean?
void signal_handle_sigchld(int sig);
#endif

int main(int argint, char *argpt[])
{
	pid_t pid = fork();

	if(0 == pid)
	{
		printf("child Sleep\n");
		sleep(3);
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
			printf("Waiting...wait() will stuck here\n");
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
#elif (defined TEST_ZOMBIE_WAITPID)
		{
			const int maxWaitTimes = 5;
			const int errorCode = -1;
			int status = 0, ret = 0;
			for (int i = 0; i < maxWaitTimes; ++i) {
				sleep(1);
				ret = waitpid(pid, &status, WNOHANG);
				printf("Waitpid, times: %d, ret(cpid): %d, status: %d, WEXITSTATUS: %d,"
						"WIFEXITED:%d\n",
						i, ret, status, WEXITSTATUS(status), WIFEXITED(status));
			}
		}
#elif (defined TEST_ZOMBIE_SIGNAL)
		{
			signal(SIGCHLD, signal_handle_sigchld);
			printf("parent sleep 15s...\n");
			sleep(15);
			printf("parent wakeup! (system will wake parent process forced to "
					"call handle func)\n");
		}
#elif (defined TEST_ZOMBIE_SIGACTION)
#endif
		{
			struct sigaction act;
			struct sigaction oldact;
			act.sa_handler = signal_handle_sigchld;
			sigemptyset(&act.sa_mask);
			act.sa_flags = 0;
			printf("parent sigaction {.sa_flags = %x}\n", act.sa_flags);
			sigaction(SIGCHLD, &act, &oldact);
			printf("parent sleep 15s...\n");
			sleep(15);
			printf("parent wakeup! (system will wake parent process forced to "
					"call handle func)\n");
			printf("parent sigaction {.sa_flags = %x}\n", act.sa_flags);
		}
#endif /* TEST_ZOMBIE */
	}
	return 0;
}

#if (defined TEST_ZOMBIE_SIGNAL) || (defined TEST_ZOMBIE_SIGACTION)
// signal handle
void signal_handle_sigchld(int sig) {
	printf("%s: recv sig: %d\n", __func__, sig);
}
#endif