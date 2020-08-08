#include <stdio.h>
#include <unistd.h>

int main(int argint, char *argpt[])
{
    pid_t pid = fork();

    if(0 == pid)
    {
        printf("child process pid didn't define a value\n");
    }
    else
    {
        printf("child pid: %d\n", pid);
    }
    return 0;
}