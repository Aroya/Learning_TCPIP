### 说明

本部分进行fork的学习，并对子process进行管理

#### define TEST_ZOMBIE_WAIT

#### #define TEST_ZOMBIE_WAITPID

standard output

> This is parent process, child pid: 276
> child Sleep
> Process zombie process
> Waitpid, times: 0, ret(cpid): 0, status: 0, WEXITSTATUS: 0,WIFEXITED:1
> Waitpid, times: 1, ret(cpid): 0, status: 0, WEXITSTATUS: 0,WIFEXITED:1
> child process's pid didn't define a value
> Waitpid, times: 2, ret(cpid): 276, status: 2560, WEXITSTATUS: 10,WIFEXITED:1
> Waitpid, times: 3, ret(cpid): -1, status: 2560, WEXITSTATUS: 10,WIFEXITED:1
> Waitpid, times: 4, ret(cpid): -1, status: 2560, WEXITSTATUS: 10,WIFEXITED:1

#### #define TEST_ZOMBIE_SIGNAL

standard output

> This is parent process, child pid: 353
> child Sleep
> Process zombie process
> parent sleep 15s...
> child process's pid didn't define a value
> signal_handle_sigchld: recv sig: 17
> parent wakeup! (system will wake parent process forced to call handle func)

#### #define TEST_ZOMBIE_SIGACTION

> This is parent process, child pid: 297
> child Sleep
> Process zombie process
> parent sigaction {.sa_flags = 0}
> parent sleep 15s...
> ^[[Achild process's pid didn't define a value
> signal_handle_sigchld: recv sig: 17
> parent wakeup! (system will wake parent process forced to call handle func)
> parent sigaction {.sa_flags = 0}