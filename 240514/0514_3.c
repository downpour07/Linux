#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main() {
	pid_t pid;
	int count = 5;

	if((pid=fork()) > 0) {
		sleep(2);
		printf("[parent] bye!\n");
		raise(SIGINT);
	}
	else if(pid == 0) {
		printf("[childe] set\n");
		kill(getppid(), SIGINT);
		printf("[childe] bye\n");
	}
	else {
		printf("fail to fork\n");
	}
}
