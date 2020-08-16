#include <stdio.h>
#include <unistd.h>

using namespace std;

int main(int argi, char *arga[])
{
	pid_t pid;
	int pipeFd[2];
	pipe(pipeFd);

	pid = fork();
	if(0 == pid) {
		const char msgToParent[] = "child send to pipe";
		sleep(1);
		printf("%s send: %s\n", __func__, msgToParent);
		write(pipeFd[1], msgToParent, sizeof(msgToParent));
	} else {
		char buffer[100];
		read(pipeFd[0], buffer, sizeof(buffer));
		printf("%s recv: %s\n", __func__, buffer);
	}
	return 0;
}